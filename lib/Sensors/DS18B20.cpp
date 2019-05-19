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

DS18B20::DS18B20() : tempDeviceAddress{0, 0, 0, 0, 0, 0, 0, 0} {
  pinMode(ONE_WIRE_BUS, FUNCTION_3);

  Serial.println("Initializing Address");

  this->oneWire = new OneWire(ONE_WIRE_BUS);
  //Serial.println("Creating One Wire");
  this->ds18b20 = new DallasTemperature(this->oneWire);
  //Serial.println("Creating DS18B20");
  ds18b20->begin();
  //Serial.println("Start Sensor");
  ds18b20->getAddress(tempDeviceAddress, 0);
  //Serial.println("Getting Address");

  ds18b20->setResolution(tempDeviceAddress, RESOLUTION);
  //Serial.println("Resolution Set");

  ds18b20->setWaitForConversion(false);
  //Serial.println("Set False");
  ds18b20->requestTemperatures();
  //Serial.println("Requesting Values");
}

DS18B20::~DS18B20() {}

float DS18B20::getValue() {
  float temp = this->ds18b20->getTempCByIndex(0);
  //Serial.print("Requesting Values :");
  this->ds18b20->requestTemperatures();
  return temp;
}