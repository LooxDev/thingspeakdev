/*
  thinkSpeakDev.h - Library for sending ThingSpeakData to thei
  api using the EtherCard.h library.
  Created by LooxDev, March 13, 2020.
  Released into the public domain.
*/

// Include library
#include "thingSpeakDev.h"

// Set writeAPIKey
const char *myWriteAPIKey = "ABCDEFGHIFKLPMNO";
// Declare library object
ThingSpeakDev tsd;

void setup()
{
  Serial.begin(57600);
  Serial.println("Starting");
  // Create object with (APIKey, No. of fields, Time to wait in sec)
  tsd = ThingSpeakDev(myWriteAPIKey, 7, 15);
  // Ask if ready, everything is right
  while (!tsd.isReady())
  {
    // Just print error, maybe try new instance creation
    Serial.println("Ceration of TSD failed");
    delay(5000);
  }
  // Set macaddr, unique on your network
  byte macaddr[6] = {0x42, 0x31, 0x20, 0x64, 0x31, 0x16};
  tsd.setMacAdress(macaddr);
  Serial.println("Ready");
}

void loop()
{
  // Wait until next interval
  /*
    Important! 
    Do not use delay(..) here because this will block the whole code
    and your network interface cant get server responses or
    even will fail 
  */
  if (!tsd.wait())
  {
    // Set test value to send (or measure etc.)
    float test = 42;
    // Set test value to field 7 (1, .., 7)
    tsd.setField(7, test);
    // Send test data
    tsd.sendData();
  }
}
