/*
  thinkSpeakDev.h - Library for sending ThingSpeakData to thei
  api using the EtherCard.h library.
  Created by Julius Monska, March 13, 2020.
  Released into the public domain.
*/

#ifndef THINGSPEAK_DEV_HPP
#define THINGSPEAK_DEV_HPP

#include <Arduino.h>
#include <EtherCard.h>

const char website[] PROGMEM = "api.thingspeak.com";

class ThingSpeakDev
{
public:
  ThingSpeakDev();
  ThingSpeakDev(const char *_key, int _numfields, int _waittime);

  void setMacAdress(byte _mac[6]);
  byte* getMacAdress();
  
  void setWaitTime(int _waittime);
  int getWaitTime();

  bool wait();
  
  void setNumFields(int _numfields);
  int getNumFields();
  
  const char *getWriteAPIKey();

  void setField(int _fieldid, float _value);
  float getField(int _fieldid);

  bool isReady();

  void sendData();

private:
  void setupEthernet();

  byte m_mac[6] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
  float *m_fields;
  int m_numfields;
  const char *m_apikey;
  int m_waittime;
  uint32_t m_timer;

  bool m_ready = false;
};

#endif
