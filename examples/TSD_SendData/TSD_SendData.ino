#include "thingSpeakDev.h"

const char *myWriteAPIKey = "ABCDEFGHIFKLPMNO";
ThingSpeakDev tsd;

void setup()
{
  Serial.begin(57600);
  Serial.println("Starting");
  tsd = ThingSpeakDev(myWriteAPIKey, 7, 15);
  while (!tsd.isReady())
  {
    Serial.println("Ceration of TSD failed");
    delay(5000);
  }
  byte macaddr[6] = {0x42, 0x31, 0x20, 0x64, 0x31, 0x16};
  tsd.setMacAdress(macaddr);
  Serial.println("Ready");
}

void loop()
{

  if (!tsd.wait())
  {
    float test = 42;

    tsd.setField(7, test);

    tsd.sendData();
  }
}
