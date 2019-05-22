///////////////////////////////////////////////////////////
//  FactorySensorManager.h
//  Implementation of the Class FactorySensorManager
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
#define EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_

#include "SensorManager.h"

class FactorySensorManager {

public:
  enum TYPE_SENSOR_MANAGER {
    AMBIENT_HUMIDITY = 0,
    AMBIENT_TEMPERATURE = 1,
    AMBIENT_PRESSURE = 2,
    SOIL_TEMP = 3,
    SOIL_HUMIDITY = 4,
    BATT_VOLTAJE = 5,
    BATT_TEMPERATURE = 6,
    BATT_STATUS = 7,
    PANEL_VOLTAJE = 8,
    ULTRAVIOLE_INDEX = 9,
    BRIGHTNESS = 10,
    VOLATILE_ORGANIC_COMPUNDS = 11,
    EPOCH = 12,
  };

  FactorySensorManager();
  virtual ~FactorySensorManager();
  SensorManager *m_sensorManager;
  SensorManager *createManager(TYPE_SENSOR_MANAGER type);

  inline String getManagerType(TYPE_SENSOR_MANAGER type) {
    String strType;
    switch (type) {
    case AMBIENT_HUMIDITY:
      strType = "AMBIENT_HUMIDITY";
      break;
    case AMBIENT_TEMPERATURE:
      strType = "AMBIENT_TEMPERATURE";
      break;
    case AMBIENT_PRESSURE:
      strType = "AMBIENT_PRESSURE";
      break;
    case SOIL_TEMP:
      strType = "SOIL_TEMP";
      break;
    case SOIL_HUMIDITY:
      strType = "SOIL_HUMIDITY";
      break;
    case BATT_VOLTAJE:
      strType = "BATT_VOLTAJE";
      break;
    case BATT_TEMPERATURE:
      strType = "BATT_TEMPERATURE";
      break;
    case BATT_STATUS:
      strType = "BATT_STATUS";
      break;
    case PANEL_VOLTAJE:
      strType = "PANEL_VOLTAJE";
      break;
    case ULTRAVIOLE_INDEX:
      strType = "ULTRAVIOLE_INDEX";
      break;
    case BRIGHTNESS:
      strType = "BRIGHTNESS";
      break;
    case VOLATILE_ORGANIC_COMPUNDS:
      strType = "VOLATILE_ORGANIC_COMPUNDS";
      break;
    case EPOCH:
      strType = "EPOCH";
      break;
    }
    return strType;
  }
};
#endif // !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
