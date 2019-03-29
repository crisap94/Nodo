///////////////////////////////////////////////////////////
//  BME680.h
//  Implementation of the Class BME680
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_)
#define EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_

#include "I2C.h"
#include "Sensor.h"

class BME680 : public Sensor, public I2C {
private:

  static BME680 *m_BME680;

  BME680();
  virtual ~BME680();

public:
  static BME680 *getInstance(){ 
	  if(m_BME680 == NULL){
		  m_BME680 = new BME680();
	  }
	  return m_BME680;
  }

  void begin();
  float getHumidity();
  float getTemperature();
  float getVOC();
  float getPressure();
};
#endif // !defined(EA_85488350_1724_4f47_A6CC_CD220A1288EC__INCLUDED_)
