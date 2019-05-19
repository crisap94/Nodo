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
  analogPin = PCF8591::PIN::BATT_TEMPERATURE_VOLTAJE;

  m_pcf8591 = PCF8591::getInstance();
}

double NTC::getValue() {

  int analogValue = m_pcf8591->analogRead(analogPin);
  
  double Vout = (analogValue * Vin) / ADC_RESOLUTION;

  // R2 NTC Resistance
  double R2 = (Vout * R1) / (Vin - Vout);

  double Tk = 1 / (((log(R2 / R_AT_25)) / (BCOEF)) + (1 / KELVIN_AT_25));

  double C = Tk - 273.15;

  return C;
}

NTC::~NTC() {}
