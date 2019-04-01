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
  this->time = new RtcDateTime(this->ds3231->GetDateTime());
  if (!this->ds3231->IsDateTimeValid()) {

    // DEBUG("RTC lost confidence in the DateTime!");

    this->ds3231->SetDateTime(*compiled);
  }
  if (!this->ds3231->GetIsRunning()) {
    // DEBUG("RTC was not actively running, starting now");
    this->ds3231->SetIsRunning(true);
  }

  if (*this->time < *compiled) {
    //  DEBUG("RTC is older than compile time!  (Updating DateTime)");
    this->ds3231->SetDateTime(*compiled);
  } else if (*this->time > *compiled) {
    //  DEBUG("RTC is newer than compile time. (this is expected)");
  } else if (*this->time == *compiled) {
    //  DEBUG("RTC is the same as compile time! (not expected but all is
    //  fine)");
  }

  // never assume the RTC was last configured by you, so
  // just clear them to your needed state
  // this->ds3231->SetSquareWavePin(DS1307SquareWaveOut::DS1307SquareWaveOut_Low);
}

DS3231::~DS3231() {}

RtcDateTime *DS3231::getTime() {

  if (!this->ds3231->IsDateTimeValid()) {
    // Common Cuases:
    //    1) the battery on the device is low or even missing and the power line
    //    was disconnected
    //  DEBUG("RTC lost confidence in the DateTime!");
  }

  return this->time;
}

void DS3231::update() {
    delete this->time;
    this->time = new RtcDateTime(this->ds3231->GetDateTime());
    
    //  DEBUG("%02u/%02u/%04u %02u:%02u:%02u", this->time->Month(),
    //        this->time->Day(), this->time->Year(), this->time->Hour(),
    //        this->time->Minute(), this->time->Second());
}

long DS3231::getValue() {
  long epoch = 123123122;
  return epoch;
}
