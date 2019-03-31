///////////////////////////////////////////////////////////
//  RT9013.cpp
//  Implementation of the Class RT9013
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "RT9013.h"
#include "ESP8266WiFi.h"

RT9013 *RT9013::m_rt9013 = NULL;

RT9013::RT9013(){
	this->m_pcf8574 = PCF8574::getInstance();
	this->pinConnection = PCF8574::PIN::RT9013_ENABLE;
}

RT9013::~RT9013(){

}

void RT9013::setStatus(RT9013::TP4056_STATUS status){
	this->m_pcf8574->setValue((PCF8574::PIN) this->pinConnection,status);
}