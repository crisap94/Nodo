///////////////////////////////////////////////////////////
//  SolarPanel.cpp
//  Implementation of the Class SolarPanel
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "SolarPanel.h"
#include "ESP8266WiFi.h"

SolarPanel *SolarPanel::m_solarPanel = NULL;

SolarPanel::SolarPanel() {
  this->m_pcf8591 = PCF8591::getInstance();
  this->pinConnection = PCF8591::PIN::PANEL_VOLTAJE;
  this->samplingInterval = 5;
}

SolarPanel::~SolarPanel() {}

float SolarPanel::getVoltaje() {
  return this->m_pcf8591->getValue((PCF8591::PIN)this->pinConnection);
}