///////////////////////////////////////////////////////////
//  BME680.h
//  Implementation of the Class BME680
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_)
#define EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_

#include <Wire.h>

#include "Sensor.h"

#include <Adafruit_Sensor.h>

#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

class BME680 : public Sensor{
private:
  int address;
  Adafruit_BME680 bme;
  static BME680 *m_bme680;

  BME680();
  virtual ~BME680();

public:
  static BME680 *getInstance() {
    if (m_bme680 == NULL) {
      m_bme680 = new BME680();
    }
    return m_bme680;
  }

  float getHumidity();
  float getTemperature();
  float getVOC();
  float getPressure();
  float getAltitude();
};
#endif // !defined(EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_)
