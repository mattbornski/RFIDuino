/**
 *  @title:  StrongLink SL018/SL030 RFID reader demo
 *  @author: marc@marcboon.com
 *  @see:    http://www.stronglink.cn/english/sl018.htm
 *  @see:    http://www.stronglink.cn/english/sl030.htm
 *
 *  Arduino to SL018/SL030 wiring:
 *  D0/SDA     2     3  (pull up to 3.3V via ~4.7kOhm resister)
 *  D1/SCL     3     4  (pull up to 3.3V via ~4.7kOhm resister)
 *  5V         4     -
 *  GND        5     6
 *  3V3        -     1
 */

#include <SL018/SL018.h>

SL018 rfid;

void setup()
{
  Wire.begin();
  Serial.begin(19200);

  // prompt for tag
  Particle.publish("Show me your tag");
}

void loop()
{
  // start seek mode
  rfid.seekTag();
  // wait until tag detected
  while(!rfid.available());
  // print tag id
  Particle.publish(rfid.getTagString());
}

