///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DataManager.h"
#include "FactorySensorManager.h"

DataManager::DataManager()
    : managers{
		FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_PRESSURE,
		FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE,
		FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_STATUS,
		FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_TEMPERATURE,
		FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_VOLTAJE,
		FactorySensorManager::TYPE_SENSOR_MANAGER::BRIGHTNESS,
		FactorySensorManager::TYPE_SENSOR_MANAGER::EPOCH,
		FactorySensorManager::TYPE_SENSOR_MANAGER::PANEL_VOLTAJE,
		FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_HUMIDITY,
		FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_TEMP,
		FactorySensorManager::TYPE_SENSOR_MANAGER::ULTRAVIOLE_INDEX,
		FactorySensorManager::TYPE_SENSOR_MANAGER::VOLATILE_ORGANIC_COMPUNDS
		} {
			this->factoryManager = new FactorySensorManager();
}

DataManager::~DataManager() {}
/**
 * @brief
 * {
    "data": {
      "temperature": "28.27",
      "humidity": 81,
      "soilHumidity": 47,
      "pressure": 1023,
      "uv": 2,
      "brightness": 643,
      "floorTemperature": 28,
      "volatileGases": 616,
      "panelvoltaje": 5,
      "timestamp": "2019-02-22T16:05:23",
      "gps": {
        "latitude": "10.399080",
        "longitude": "-75.504142"
      },
      "batteryVoltaje": "4.1927",
      "batteryTmeperature": 30
    },
    "zoneId": "5ac012583e194204e0afef6b",
    "firmwareVersion": "V1.0",
    "config": {
      "mac": "24-EC-64-A1-A7-C4",
      "rssi": "-67",
      "channel": 13
    }
  }
 * @return const char*
 */
const char *DataManager::getPayload() {
	DynamicJsonDocument doc(700);

	doc["sensor"] = "gps";
	doc["time"] = 1351824120;

	JsonArray data = doc.createNestedArray("data");
	data.add(48.756080);
	data.add(2.302038);

}