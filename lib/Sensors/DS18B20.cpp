///////////////////////////////////////////////////////////
//  DS18B20.cpp
//  Implementation of the Class DS18B20
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DS18B20.h"
#include "ESP8266WiFi.h"

DS18B20 *DS18B20::m_ds18b20 = NULL;

DS18B20::DS18B20() { randomSeed(analogRead(A0)); }

DS18B20::~DS18B20(){

}

void DS18B20::begin(){

}


float DS18B20::getValue(){
	return random(25,27);
}