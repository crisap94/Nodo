///////////////////////////////////////////////////////////
//  Battery.cpp
//  Implementation of the Class Battery
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "Battery.h"
#include "ESP8266WiFi.h"

Battery *Battery::m_battery = NULL;

Battery::Battery(){
	pinConnection = PCF8591::PIN::BATT_VOLTAJE;
	m_pcf8591 = PCF8591::getInstance();
	m_tp4056 = TP4056::getInstance();
	m_ntc = NTC::getInstance();
}

Battery::~Battery(){

}

float Battery::getTemp(){
	return m_ntc->getValue();
}


float Battery::getVoltaje(){
  float BattVoltaje = (m_pcf8591->analogRead((PCF8591::PIN)pinConnection) * 4.2)/ADC_RESOLUTION;
  return BattVoltaje;
}

boolean Battery::getStatus(){
	return m_tp4056->getStatus();
}