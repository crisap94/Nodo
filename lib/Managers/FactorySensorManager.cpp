///////////////////////////////////////////////////////////
//  FactorySensorManager.cpp
//  Implementation of the Class FactorySensorManager
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "FactorySensorManager.h"

#include "AmbientHumidityManager.h"
#include "AmbientTemperatureManager.h"
#include "AtmosphericPressureManager.h"
#include "BatteryStatusManager.h"
#include "BatteryTemperatureManager.h"
#include "BatteryVoltajeManager.h"
#include "BrightnessManager.h"
#include "RTCManager.h"
#include "RelativeHumidityManager.h"
#include "SoilMoistureManager.h"
#include "SoilTempManager.h"
#include "SolarPanelVoltajeManager.h"
#include "UltraVioletIndexManager.h"
#include "VolatileOrganicCompoundsManager.h"


FactorySensorManager::FactorySensorManager() {}

FactorySensorManager::~FactorySensorManager() {}

SensorManager *FactorySensorManager::createManager(TYPE_SENSOR_MANAGER type) {

  switch (type) {
  case AMBIENT_HUMIDITY:
    m_sensorManager = new AmbientHumidityManager();
    break;
  case AMBIENT_PRESSURE:
    m_sensorManager = new AtmosphericPressureManager();
    break;
  case AMBIENT_TEMPERATURE:
    m_sensorManager = new AmbientTemperatureManager();
    break;
  case SOIL_HUMIDITY:
    m_sensorManager = new SoilMoistureManager();
    break;
  case SOIL_TEMP:
    m_sensorManager = new SoilTempManager();
    break;
  case BRIGHTNESS:
    m_sensorManager = new BrightnessManager();
    break;
  case ULTRAVIOLE_INDEX:
    m_sensorManager = new UltraVioletIndexManager();
    break;
  case BATT_STATUS:
    m_sensorManager = new BatteryStatusManager();
    break;
  case BATT_TEMPERATURE:
    m_sensorManager = new BatteryTemperatureManager();
    break;
  case BATT_VOLTAJE:
    m_sensorManager = new BatteryVoltajeManager();
    break;
  case PANEL_VOLTAJE:
    m_sensorManager = new SolarPanelVoltajeManager();
    break;
  case VOLATILE_ORGANIC_COMPUNDS:
    m_sensorManager = new VolatileOrganicCompoundsManager();
    break;
  case EPOCH:
    m_sensorManager = new RTCManager();
    break;
  }
  return m_sensorManager;
}