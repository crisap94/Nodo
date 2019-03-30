///////////////////////////////////////////////////////////
//  CapacitiveSoilMoisture.cpp
//  Implementation of the Class CapacitiveSoilMoisture
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "CapacitiveSoilMoisture.h"
#include "Arduino.h"

CapacitiveSoilMoisture *CapacitiveSoilMoisture::m_CapacitiveSoilMoisture = NULL;

CapacitiveSoilMoisture::CapacitiveSoilMoisture() {
  this->m_pcf8591 = PCF8591::getInstance();
  this->pinConnection = PCF8591::PIN::SOIL_HUMIDITY_VOLTAJE;
  this->samplingInterval = 5;
}

CapacitiveSoilMoisture::~CapacitiveSoilMoisture() {}

float CapacitiveSoilMoisture::getValue() {
  return this->m_pcf8591->getValue((PCF8591::PIN)this->pinConnection);
}
