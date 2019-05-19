///////////////////////////////////////////////////////////
//  NTC.cpp
//  Implementation of the Class NTC
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

/**
        The class implements a set of methods of the NTC_Thermistor.h
        interface for working with a NTC thermistor and reading
        a temperature in Celsius, Fahrenheit and Kelvin.

        https://github.com/YuriiSalimov/NTC_Thermistor

        Created by Yurii Salimov, February, 2018.
        Released into the public domain.
*/

#include "NTC.h"
#include "ESP8266WiFi.h"

NTC *NTC::m_ntc = NULL;

NTC::NTC() {
  pin = PCF8591::PIN::BATT_TEMPERATURE_VOLTAJE;
  referenceResistance = 8000;
  nominalResistance = 100000;
  nominalTemperature = 25;
  bValue = 3950;
  m_pcf8591 = PCF8591::getInstance();

}

double NTC::readCelsius() { return kelvinsToCelsius(readKelvin()); }

double NTC::readFahrenheit() { return kelvinsToFahrenheit(readKelvin()); }

double NTC::readFarenheit() { return readFahrenheit(); }

double NTC::readKelvin() { return resistanceToKelvins(readResistance()); }

inline double NTC::resistanceToKelvins(const double resistance) {
  const double inverseKelvin =
      1.0 / nominalTemperature +
      1.0 / bValue * log(resistance / nominalResistance);
  return (1.0 / (inverseKelvin));
}

inline double NTC::readResistance() {
  return referenceResistance / (NTC_ADC / readVoltage());
}

inline double NTC::readVoltage() {
  //Serial.println(m_pcf8591->getValue((PCF8591::PIN)pin));
  return m_pcf8591->voltageRead((PCF8591::PIN)pin);
}

inline double NTC::celsiusToKelvins(const double celsius) {
  return (celsius + 273.15);
}

inline double NTC::kelvinsToCelsius(const double kelvins) {
  return (kelvins - 273.15);
}

inline double NTC::celsiusToFahrenheit(const double celsius) {
  return (celsius * 1.8 + 32);
}

NTC::~NTC() {}

float NTC::getValue() { return m_ntc->readCelsius(); }
