///////////////////////////////////////////////////////////
//  FactorySensorManager.h
//  Implementation of the Class FactorySensorManager
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
#define EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_

#include "Arduino.h"
#include "SensorManager.h"


enum TYPE_SENSOR_MANAGER {
  AMBIENT_HUMIDITY,
  AMBIENT_TEMPERATURE,
  AMBIENT_PRESSURE,
  SOIL_TEMP,
  SOIL_HUMIDITY,
  BATT_VOLTAJE,
  BATT_TEMPERATURE,
  BATT_STATUS,
  PANEL_VOLTAJE,
  ULTRAVIOLE_INDEX,
  BRIGHTNESS,
  VOLATILE_ORGANIC_COMPUNDS,
  EPOCH
};

class FactorySensorManager {

public:
  FactorySensorManager();
  virtual ~FactorySensorManager();

  SensorManager *createManager(TYPE_SENSOR_MANAGER type);
  
};
#endif // !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
