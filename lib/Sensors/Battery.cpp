///////////////////////////////////////////////////////////
//  Battery.cpp
//  Implementation of the Class Battery
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "Battery.h"
#include "Arduino.h"

Battery *Battery::m_battery = NULL;

Battery::Battery(){
	this->pinConnection = PCF8591::PIN::BATT_VOLTAJE;
	this->m_pcf8591 = PCF8591::getInstance();
	this->m_tp4056 = TP4056::getInstance();
	this->m_ntc = NTC::getInstance();
}

Battery::~Battery(){

}

float Battery::getTemp(){
	return this->m_ntc->getValue();
}


float Battery::getVoltaje(){
  return this->m_pcf8591->getValue((PCF8591::PIN)pinConnection);
}

boolean Battery::getStatus(){
	return m_tp4056->getStatus();
}