///////////////////////////////////////////////////////////
//  AmbientTemperatureManager.h
//  Implementation of the Class AmbientTemperatureManager
//  Created on:      28-Mar-2019 4:29:31 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(_AmbientHumidityManager_)
#define _AmbientHumidityManager_

#include "SensorManager.h"
#include "BME680.h"

class AmbientHumidityManager : public SensorManager
{
private:
  float getData() { return BME680::getInstance()->getHumidity(); }

public:
  AmbientHumidityManager(){};
  virtual ~AmbientHumidityManager(){};
};
#endif // !defined(AmbientHumidityManager)