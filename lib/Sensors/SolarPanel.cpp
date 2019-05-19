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
  m_pcf8591 = PCF8591::getInstance();
  pinConnection = PCF8591::PIN::PANEL_VOLTAJE;
  samplingInterval = 5;
}

SolarPanel::~SolarPanel() {}

float SolarPanel::getVoltaje() {
  float panelVoltaje = (m_pcf8591->analogRead((PCF8591::PIN)pinConnection) * 6.0)/ADC_RESOLUTION;
  return panelVoltaje;
}