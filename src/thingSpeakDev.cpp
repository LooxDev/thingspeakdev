/*
  thinkSpeakDev.cpp - Library for sending ThingSpeakData to their
  api using the EtherCard.h library.
  Created by LooxDev, March 13, 2020.
  Released into the public domain.
*/

#include "thingSpeakDev.h"

uint8_t Ethernet::buffer[700];

//------------------------------------------------------------------------------
ThingSpeakDev::ThingSpeakDev()
{
  m_numfields = 1;
  m_fields = new double[1];
  m_fields[0] = 0.0;
  m_apikey = "";
  m_waittime = 300;
  m_timer = millis();
}
ThingSpeakDev::ThingSpeakDev(const char *_key, int _numfields, uint32_t _waittime)
{
  m_numfields = _numfields;
  m_fields = new double[m_numfields];
  for (int i = 0; i < m_numfields; i++)
  {
    m_fields[i] = 0.0;
  }
  m_apikey = _key;
  m_waittime = _waittime;
  m_timer = millis();
  this->setupEthernet();
}
//------------------------------------------------------------------------------
void ThingSpeakDev::setMacAdress(byte *_mac)
{
  m_mac[0] = _mac[0];
  m_mac[1] = _mac[1];
  m_mac[2] = _mac[2];
  m_mac[3] = _mac[3];
  m_mac[4] = _mac[4];
  m_mac[5] = _mac[5];
}
byte *ThingSpeakDev::getMacAdress()
{
  return m_mac;
}
//------------------------------------------------------------------------------
void ThingSpeakDev::setWaitTime(uint32_t _waittime)
{
  m_waittime = _waittime;
}
uint32_t ThingSpeakDev::getWaitTime()
{
  return m_waittime;
}
//------------------------------------------------------------------------------
bool ThingSpeakDev::wait()
{
  ether.packetLoop(ether.packetReceive());
  return millis() < m_timer;
}
//------------------------------------------------------------------------------
void ThingSpeakDev::setNumFields(int _numfields)
{
  m_numfields = _numfields;
  m_fields = new double[m_numfields];
  for (int i = 0; i < m_numfields; i++)
  {
    m_fields[i] = 0;
  }
}
int ThingSpeakDev::getNumFields()
{
  return m_numfields;
}
//------------------------------------------------------------------------------
const char *ThingSpeakDev::getWriteAPIKey()
{
  return m_apikey;
}
//------------------------------------------------------------------------------
void ThingSpeakDev::setField(int _fieldid, double _value)
{
  if (_fieldid <= 0 || _fieldid > m_numfields)
  {
    return;
  }
  m_fields[_fieldid - 1] = _value;
}
double ThingSpeakDev::getField(int _fieldid)
{
  if (_fieldid <= 0 || _fieldid > m_numfields)
  {
    return -1000;
  }
  return m_fields[_fieldid - 1];
}
//------------------------------------------------------------------------------
bool ThingSpeakDev::isReady()
{
  return m_ready;
}
//------------------------------------------------------------------------------
static void ts_callback(byte status, word off, word len)
{
  if (status != 0)
  {
    Serial.println(" ERROR >>>");
    Ethernet::buffer[off + 300] = 0;
    Serial.print((const char *)Ethernet::buffer + off);
    Serial.println("...");
  }
  else
  {
    Serial.println(" OK >>>");
    Ethernet::buffer[off + 300] = 0;
  }
}
//------------------------------------------------------------------------------
void ThingSpeakDev::sendData()
{
  ether.packetLoop(ether.packetReceive());

  char data[25 + m_numfields * 16];
  int len = 0;
  len += sprintf(data, "%s%s", "api_key=", m_apikey);
  for (int i = 0; i < m_numfields; i++)
  {
    char *val = new char[7];
    dtostrf(m_fields[i], 4, 2, val);
    len += sprintf(data + len, "%s%d%s%s", "&field", i + 1, "=", val);
  }
  Serial.print("[TSD] Data to be send: ");
  Serial.println(data);
  char *test = new char[len + 1];
  strncpy(test, data, len + 1);
  Serial.print("[TSD] <<< Request pending...");
  ether.browseUrl(PSTR("/update.php?"), test, website, ts_callback);

  m_timer = millis() + (m_waittime * 1000);
}
void ThingSpeakDev::setupEthernet()
{
  if (ether.begin(sizeof Ethernet::buffer, m_mac) == 0)
  {
    // handle failure to initiate network interface
    Serial.println("[TSD] Failed to access Ethernet controller");
    return;
  }
  if (!ether.dhcpSetup())
  {
    // handle failure to obtain IP address via DHCP
    Serial.println("[TSD] DHCP failed");
    return;
  }
  ether.printIp("[TSD] IP:  ", ether.myip);
  ether.printIp("[TSD] GW:  ", ether.gwip);
  ether.printIp("[TSD] DNS: ", ether.dnsip);
  if (!ether.dnsLookup(website))
  {
    // handle failure to obtain IP address for given website
    Serial.println("[TSD] DNS of thingspeak website failed");
    return;
  }
  ether.printIp("[TSD] SRV: ", ether.hisip);
  this->m_ready = true;
}
