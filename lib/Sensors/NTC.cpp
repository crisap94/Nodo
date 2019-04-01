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
  this->pin = PCF8591::PIN::BATT_TEMPERATURE_VOLTAJE;
  this->referenceResistance = 8000;
  this->nominalResistance = 100000;
  this->nominalTemperature = 25;
  this->bValue = 3950;
  this->m_pcf8591 = PCF8591::getInstance();
  this->readingsNumber = 10;
}

double NTC::readCelsius() { return kelvinsToCelsius(readKelvin()); }

double NTC::readFahrenheit() { return kelvinsToFahrenheit(readKelvin()); }

double NTC::readFarenheit() { return readFahrenheit(); }

double NTC::readKelvin() { return resistanceToKelvins(readResistance()); }

inline double NTC::resistanceToKelvins(const double resistance) {
  const double inverseKelvin =
      1.0 / this->nominalTemperature +
      1.0 / this->bValue * log(resistance / this->nominalResistance);
  return (1.0 / (inverseKelvin));
}

inline double NTC::readResistance() {
  return this->referenceResistance / (NTC_ADC / readVoltage() - 1);
}

inline double NTC::readVoltage() {
  return this->m_pcf8591->getValue((PCF8591::PIN )this->pin);
}

void NTC::setReadingsNumber(const int newReadingsNumber) {
  this->readingsNumber =
      validate(newReadingsNumber, NTC_DEFAULT_READINGS_NUMBER);
}

template <typename A, typename B>
A NTC::validate(const A data, const B alternative) {
  return (data > 0) ? data : alternative;
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

float NTC::getValue() {
  return this->m_ntc->readCelsius();
}
