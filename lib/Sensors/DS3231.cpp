///////////////////////////////////////////////////////////
//  DS3231.cpp
//  Implementation of the Class DS3231
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DS3231.h"
#include "ESP8266WiFi.h"

#include "RtcDS3231.h"

DS3231 *DS3231::m_ds3231 = NULL;

DS3231::DS3231() {
  this->ds3231 = new RtcDS3231<TwoWire>(Wire);
  this->ds3231->Begin();
  RtcDateTime *compiled = new RtcDateTime(__DATE__, __TIME__);
  this->m_time = new RtcDateTime(this->ds3231->GetDateTime());
  if (!this->ds3231->IsDateTimeValid()) {

    // DEBUG("RTC lost confidence in the DateTime!");

    this->ds3231->SetDateTime(*compiled);
  }
  if (!this->ds3231->GetIsRunning()) {
    // DEBUG("RTC was not actively running, starting now");
    this->ds3231->SetIsRunning(true);
  }

  if (*this->m_time < *compiled) {
    //  DEBUG("RTC is older than compile m_time!  (Updating DateTime)");
    this->ds3231->SetDateTime(*compiled);
  } else if (*this->m_time > *compiled) {
    //  DEBUG("RTC is newer than compile m_time. (this is expected)");
  } else if (*this->m_time == *compiled) {
    //  DEBUG("RTC is the same as compile m_time! (not expected but all is
    //  fine)");
  }

  // never assume the RTC was last configured by you, so
  // just clear them to your needed state
  // this->ds3231->SetSquareWavePin(DS1307SquareWaveOut::DS1307SquareWaveOut_Low);
}

DS3231::~DS3231() {}


uint64_t DS3231::getValue() {
  uint64_t epoch = 0;
  if (!this->ds3231->IsDateTimeValid()) {
    // Common Cuases:
    //    1) the battery on the device is low or even missing and the power line
    //    was disconnected
    //  DEBUG("RTC lost confidence in the DateTime!");
    return epoch;
  }
  delete m_time;
  m_time = new RtcDateTime(ds3231->GetDateTime());
  epoch = m_time->Epoch64Time();

  return epoch;
}
