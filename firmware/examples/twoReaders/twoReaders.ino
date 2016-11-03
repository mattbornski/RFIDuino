/**
 *  @title:  StrongLink SL018/SL030 RFID 2-reader demo
 *  @author: lukasz.szostek@gmail.com based on code of:
 *  @author: marc@marcboon.com
 *  @see:    http://www.stronglink.cn/english/sl018.htm
 *  @see:    http://www.stronglink.cn/english/sl030.htm
 *
 *  Arduino to SL018/SL030 wiring:
 *  D0/SDA     2     3  (pull up to RFID reader voltage via ~4.7kOhm resistor)
 *  D1/SCL     3     4  (pull up to RFID reader voltage via ~4.7kOhm resistor)
 *  5V         4     -
 *  GND        5     6
 *  3V3        -     1
 *  5          1     5 // first reader
 *  4          1     5 // second reader
 */

#include <SL018/SL018.h>

//pins to listen for the RFID board signalling that it has detected a tag
int reader1OutPin = 5;
int reader2OutPin = 4;
const char* tagString;

SL018 rfid1;
SL018 rfid2;

void setup()
{
  //make sure these two addresses match your reader configuration
  rfid1.address = 0x50;
  rfid2.address = 0x52;
  pinMode(reader1OutPin, INPUT);
  pinMode(reader2OutPin, INPUT);
  
  if (!Particle.connected()) {
    Particle.connect();
  }
  
  if (!Wire.isEnabled()) {
    Wire.begin();
  }

  // prompt for tag
  Particle.publish("Show me your tag");
}

void loop()
{
  //if the board has signalled that it found a tag
  if(!digitalRead(reader1OutPin)) 
  {
    //query tag data
	rfid1.seekTag();
	
	/* for some reason the loop defined as:
    while(!digitalRead(reader1OutPin) || !rfid1.available());
	does not work so we need a workaround:*/
    
	//while we are waiting for data
	while(!rfid1.available()) {
	  //break if the tag has been removed
      if (digitalRead(reader1OutPin)) {
        break;
      };
    };
    tagString = rfid1.getTagString();
    Particle.publish("reader 1", tagString);
	//wait a while before querying the tag again
    delay(1500);
  };
  
  //"in parallel" we wait for the other reader
  if(!digitalRead(reader2OutPin)) 
  {
    rfid2.seekTag();
    while(!rfid2.available()) {
      if (digitalRead(reader2OutPin)) {
        break;
      };
    };
    tagString = rfid2.getTagString();
    Particle.publish("reader 2", tagString);
    delay(1500);  
  };
}