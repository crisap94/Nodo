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
  pinMode(ONE_WIRE_BUS, FUNCTION_3);

  this->oneWire = new OneWire(ONE_WIRE_BUS);
  this->ds18b20 = new DallasTemperature(this->oneWire);

  ds18b20->begin();
  ds18b20->getAddress(*tempDeviceAddress, 0);
  ds18b20->setResolution(*tempDeviceAddress, RESOLUTION);

  ds18b20->setWaitForConversion(false);
  ds18b20->requestTemperatures();

}

DS18B20::~DS18B20() {}

float DS18B20::getValue() {
  float temp = this->ds18b20->getTempCByIndex(0);
  this->ds18b20->requestTemperatures();
  return temp;
}