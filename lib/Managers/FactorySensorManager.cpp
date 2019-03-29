///////////////////////////////////////////////////////////
//  FactorySensorManager.cpp
//  Implementation of the Class FactorySensorManager
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "FactorySensorManager.h"

#include "AmbientTemperatureManager.h"
#include "AtmosphericPressureManager.h"
#include "BatteryStatusManager.h"
#include "BatteryTemperatureManager.h"
#include "BatteryVoltajeManager.h"
#include "SoilMoistureManager.h"
#include "SoilTempManager.h"
#include "SolarPanelVoltajeManager.h"
#include "BrightnessManager.h"
#include "RelativeHumidityManager.h"
#include "RTCManager.h"
#include "UltraVioletIndexManager.h"
#include "VolatileOrganicCompoundsManager.h"

FactorySensorManager::FactorySensorManager()
{
}

FactorySensorManager::~FactorySensorManager()
{
}

SensorManager *FactorySensorManager::createManager(TYPE_SENSOR_MANAGER type)
{
    SensorManager *sensorManager = new SensorManager();
    switch (type)
    {
    case AMBIENT_HUMIDITY:
        sensorManager = new AmbientTemperatureManager();
        break;
    case AMBIENT_PRESSURE:
        sensorManager = new AtmosphericPressureManager();
        break;
    case AMBIENT_TEMPERATURE:
        sensorManager = new AmbientTemperatureManager();
        break;
    case SOIL_HUMIDITY:
        sensorManager = new SoilMoistureManager();
        break;
    case SOIL_TEMP:
        sensorManager = new SoilTempManager();
        break;
    case BRIGHTNESS:
        sensorManager = new BrightnessManager();
        break;
    case ULTRAVIOLE_INDEX:
        sensorManager = new UltraVioletIndexManager();
        break;
    case BATT_STATUS:
        sensorManager = new BatteryStatusManager();
        break;
    case BATT_TEMPERATURE:
        sensorManager = new BatteryTemperatureManager();
        break;
    case BATT_VOLTAJE:
        sensorManager = new BatteryVoltajeManager();
        break;
    case PANEL_VOLTAJE:
        sensorManager = new SolarPanelVoltajeManager();
        break;
    case VOLATILE_ORGANIC_COMPUNDS:
        sensorManager = new VolatileOrganicCompoundsManager();
        break;
    case EPOCH:
        sensorManager = new RTCManager();
        break;

    }
    return sensorManager;
}