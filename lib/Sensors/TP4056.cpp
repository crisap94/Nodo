///////////////////////////////////////////////////////////
//  TP4056.cpp
//  Implementation of the Class TP4056
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "TP4056.h"
#include "ESP8266WiFi.h"

TP4056 *TP4056::m_tp4056 = NULL;

TP4056::TP4056() {
  this->m_pcf8574 = PCF8574::getInstance();
  this->pinChrg = PCF8574::PIN::TP4056_CHRG_STATUS;
  this->pinStby = PCF8574::PIN::TP4056_STDBY;
  this->pinEnable = PCF8574::PIN::TP4056_ENABLE;
}

TP4056::~TP4056() {}

boolean TP4056::getStatus() {

  boolean status = false;

  boolean charging = this->m_pcf8574->getValue((PCF8574::PIN)this->pinChrg);
  boolean standBy = this->m_pcf8574->getValue((PCF8574::PIN)this->pinStby);

  if (charging == true && standBy == false) {
    status = STAND_BY;
  } else if (charging == false && standBy == true) {
    status = CHARGING;
  }

  return status;
}
