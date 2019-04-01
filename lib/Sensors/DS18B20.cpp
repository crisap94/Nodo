///////////////////////////////////////////////////////////
//  DS18B20.cpp
//  Implementation of the Class DS18B20
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "OneWire.h"

#include "DS18B20.h"

#include "ESP8266WiFi.h"

#include <DallasTemperature.h>

DS18B20 *DS18B20::m_ds18b20 = NULL;

DS18B20::DS18B20() {
  this->oneWire = new OneWire(ONE_WIRE_BUS);
  this->ds18b20 = new DallasTemperature(this->oneWire);

  this->ds18b20->begin();
}

DS18B20::~DS18B20() {}

float DS18B20::getValue() {
  this->ds18b20->requestTemperatures();
  float temp = this->ds18b20->getTempCByIndex(0);
  return temp;
}