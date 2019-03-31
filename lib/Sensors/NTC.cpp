///////////////////////////////////////////////////////////
//  NTC.cpp
//  Implementation of the Class NTC
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "NTC.h"
#include "ESP8266WiFi.h"

NTC *NTC::m_ntc = NULL;

NTC::NTC() {
  this->m_pcf8591 = PCF8591::getInstance();
  this->pinConnection = PCF8591::PIN::BATT_TEMPERATURE_VOLTAJE;
  this->samplingInterval = 5;
}

NTC::~NTC() {}

float NTC::getValue() {
  return this->m_pcf8591->getValue((PCF8591::PIN)this->pinConnection);
}
