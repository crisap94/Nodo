///////////////////////////////////////////////////////////
//  CapacitiveSoilMoisture.cpp
//  Implementation of the Class CapacitiveSoilMoisture
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "CapacitiveSoilMoisture.h"

CapacitiveSoilMoisture *CapacitiveSoilMoisture::m_CapacitiveSoilMoisture = NULL;

CapacitiveSoilMoisture::CapacitiveSoilMoisture() {
  m_pcf8591 = PCF8591::getInstance();
  pinConnection = PCF8591::PIN::SOIL_HUMIDITY_VOLTAJE;
}

CapacitiveSoilMoisture::~CapacitiveSoilMoisture() {}

float CapacitiveSoilMoisture::getValue() {
  float analogValue = m_pcf8591->analogRead((PCF8591::PIN)pinConnection);

  return (analogValue*100)/ADC_RESOLUTION;
}
