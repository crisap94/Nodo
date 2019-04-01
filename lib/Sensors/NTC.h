///////////////////////////////////////////////////////////
//  NTC.h
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

#if !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
#define EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_

#include "Sensor.h"
#include "pcf8591.h"

/**
        Min value of Arduino ADC.
*/
#define NTC_ADC_MIN 0

/**
        Max value of Arduino ADC.
*/
#define NTC_ADC_MAX 1023

/**
        Values diapason of Arduino ADC
*/
#define NTC_ADC ((NTC_ADC_MAX) - (NTC_ADC_MIN))

#define NTC_DEFAULT_READINGS_NUMBER 5
#define NTC_DEFAULT_DELAY_TIME 10

class NTC : public Sensor {
private:
  static NTC *m_ntc;

  PCF8591 *m_pcf8591;

  int pin; // an analog port.
  double referenceResistance;
  double nominalResistance;
  double nominalTemperature; // in Celsius.
  double bValue;
  int readingsNumber;

  NTC();

  virtual ~NTC();
  
  inline double readResistance();

  inline double readVoltage();

  inline double resistanceToKelvins(double resistance);

  inline double celsiusToKelvins(double celsius);

  inline double kelvinsToCelsius(double kelvins);

  inline double celsiusToFahrenheit(double celsius);

  inline double kelvinsToFahrenheit(double kelvins);

  template <typename A, typename B> A validate(A data, B alternative);

public:
  static NTC *getInstance() {
    if (m_ntc == NULL) {
      m_ntc = new NTC();
    }
    return m_ntc;
  }

  float getValue();

  double readCelsius();

  double readKelvin();

  double readFahrenheit();

  double readFarenheit();

  void setReadingsNumber(int newReadingsNumber);

};
#endif // !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
