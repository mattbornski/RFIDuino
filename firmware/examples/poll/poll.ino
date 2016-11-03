/**
 *  @title:  StrongLink SL018/SL030 RFID reader demo
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
 */

#include "SL018/SL018.h"

SL018 rfid;

void setup()
{
  if (!Particle.connected()) {
    Particle.connect();
  }
  
  if (!Wire.isEnabled()) {
    Wire.begin();
  }
}

void loop()
{
  Particle.publish("Show me your tag");

  // start seek mode
  rfid.seekTag();
  // wait until tag detected
  while(!rfid.available());
  // print tag id
  Particle.publish(rfid.getTagString());
}
