///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DataManager.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "FactorySensorManager.h"

DataManager::DataManager()
    : managers{FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE,
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
               FactorySensorManager::TYPE_SENSOR_MANAGER::
                   VOLATILE_ORGANIC_COMPUNDS} {
  this->m_factoryManager = new FactorySensorManager();
}

DataManager::~DataManager() {}

void DataManager::getVariableData() {
  for (int i = 0; i < 13; i++) {
    m_factoryManager->createManager(this->managers[i])->getValue();
  }
}

void DataManager::getPayload(char *json_array[700]) {
  const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) +
                          JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(13);
  DynamicJsonDocument doc(capacity);

  JsonObject data = doc.createNestedObject("data");
  data["temperature"] = this->data->ambientTemperature;
  data["humidity"] = this->data->ambientHumidity;
  data["soilHumidity"] = this->data->soilHumidity;
  data["pressure"] = this->data->ambientPressure;
  data["uv"] = this->data->ambientUv;
  data["brightness"] = this->data->ambientBrightness;
  data["floorTemperature"] = this->data->soilTemperature;
  data["volatileGases"] = this->data->ambientVoc;
  data["panelvoltaje"] = this->data->panelVoltaje;
  data["timestamp"] = this->data->epoch;

  JsonObject data_gps = data.createNestedObject("gps");
  data_gps["latitude"] = "10.399080";
  data_gps["longitude"] = "-75.504142";

  data["batteryVoltaje"] = this->data->battVoltaje;
  data["batteryTmeperature"] = this->data->battTemperature;

  doc["zoneId"] = "5ac012583e194204e0afef6b";
  doc["firmwareVersion"] = "V1.0";

  JsonObject config = doc.createNestedObject("config");
  config["mac"] = "24-EC-64-A1-A7-C4";
  config["rssi"] = "-67";
  config["channel"] = 13;

  char payload[capacity];
  serializeJson(doc, payload);
  strcpy_P(*json_array, payload);
}