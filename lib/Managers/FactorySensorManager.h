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

class FactorySensorManager {

public:
  enum TYPE_SENSOR_MANAGER {
    AMBIENT_HUMIDITY            = 0,
    AMBIENT_TEMPERATURE         = 1,
    AMBIENT_PRESSURE            = 2,
    SOIL_TEMP                   = 3,
    SOIL_HUMIDITY               = 4,
    BATT_VOLTAJE                = 5,
    BATT_TEMPERATURE            = 6,
    BATT_STATUS                 = 7,
    PANEL_VOLTAJE               = 8,
    ULTRAVIOLE_INDEX            = 9,
    BRIGHTNESS                  = 10,
    VOLATILE_ORGANIC_COMPUNDS   = 11,
    EPOCH                       = 12,
  };
  FactorySensorManager();
  virtual ~FactorySensorManager();

  SensorManager *createManager(TYPE_SENSOR_MANAGER type);
};
#endif // !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
