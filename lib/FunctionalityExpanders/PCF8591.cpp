///////////////////////////////////////////////////////////
//  PCF8591.cpp
//  Implementation of the Class PCF8591
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "PCF8591.h"
#include "ESP8266WiFi.h"


PCF8591 *PCF8591::m_pcf8591 = NULL;

PCF8591::PCF8591() { randomSeed(analogRead(A0)); }

PCF8591::~PCF8591() {}

void PCF8591::begin(){
  
}

float PCF8591::getValue(PCF8591::PIN _pin) {
  float value = -1;
  switch (_pin) {
  case PCF8591::PIN::BATT_TEMPERATURE_VOLTAJE:
    value = random(100, 110);
    break;
  case PCF8591::PIN::BATT_VOLTAJE:
    value = random(220, 255);
    break;
  case PCF8591::PIN::PANEL_VOLTAJE:
    value = random(50, 100);
    break;
  case PCF8591::PIN::SOIL_HUMIDITY_VOLTAJE:
    value = random(0, 10);
    break;
  }
  return value;
}