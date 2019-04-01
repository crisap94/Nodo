///////////////////////////////////////////////////////////
//  BME680.cpp
//  Implementation of the Class BME680
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "BME680.h"
#include "ESP8266WiFi.h"

BME680 *BME680::m_bme680 = NULL;

/**
 * @brief Construct a new BME680::BME680 object
 * TODO Debug message constructing the BME680
 * ú
 */
BME680::BME680() {

  this->address = 0x77;

  if (!this->bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
  }

  // Set up oversampling and filter initialization
  this->bme.setTemperatureOversampling(BME680_OS_8X);
  this->bme.setHumidityOversampling(BME680_OS_2X);
  this->bme.setPressureOversampling(BME680_OS_4X);
  this->bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  this->bme.setGasHeater(320, 150); // 320*C for 150 ms
}

/**
 * @brief Destroy the BME680::BME680 object
 * TODO Debug Message destroying the BME680
 * ú
 */
BME680::~BME680() {}

float BME680::getHumidity() {
  this->bme.performReading();
  return this->bme.humidity;
}
float BME680::getTemperature() {
  this->bme.performReading();
  return this->bme.temperature;
}
float BME680::getVOC() {
  this->bme.performReading();
  return this->bme.gas_resistance / 1000.0;
}
float BME680::getPressure() {
  this->bme.performReading();
  return this->bme.pressure / 100.0;
}
float BME680::getAltitude() {
  this->bme.performReading();
  return this->bme.readAltitude(SEALEVELPRESSURE_HPA);
}
