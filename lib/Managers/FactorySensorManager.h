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
    switch (type) {
    case AMBIENT_HUMIDITY:
      return "AMBIENT_HUMIDITY";
      break;
    case AMBIENT_TEMPERATURE:
      return "AMBIENT_TEMPERATURE";
      break;
    case AMBIENT_PRESSURE:
      return "AMBIENT_PRESSURE";
      break;
    case SOIL_TEMP:
      return "SOIL_TEMP";
      break;
    case SOIL_HUMIDITY:
      return "SOIL_HUMIDITY";
      break;
    case BATT_VOLTAJE:
      return "BATT_VOLTAJE";
      break;
    case BATT_TEMPERATURE:
      return "BATT_TEMPERATURE";
      break;
    case BATT_STATUS:
      return "BATT_STATUS";
      break;
    case PANEL_VOLTAJE:
      return "PANEL_VOLTAJE";
      break;
    case ULTRAVIOLE_INDEX:
      return "ULTRAVIOLE_INDEX";
      break;
    case BRIGHTNESS:
      return "BRIGHTNESS";
      break;
    case VOLATILE_ORGANIC_COMPUNDS:
      return "VOLATILE_ORGANIC_COMPUNDS";
      break;
    case EPOCH:
      return "EPOCH";
      break;
    }
  }
};
#endif // !defined(EA_6BFF658B_B0A6_4437_B8D6_A5614E83D114__INCLUDED_)
