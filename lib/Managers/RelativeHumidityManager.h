///////////////////////////////////////////////////////////
//  RelativeHumidityManager.h
//  Implementation of the Class RelativeHumidityManager
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_)
#define EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_

#include "SensorManager.h"
#include "BME680.h"
class RelativeHumidityManager : public SensorManager
{
  private:
	float getData() { return BME680::getInstance()->getHumidity(); }

  public:
	RelativeHumidityManager(){};
	virtual ~RelativeHumidityManager(){};

};
#endif // !defined(EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_)
