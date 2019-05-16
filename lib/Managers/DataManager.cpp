///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DataManager.h"
#include "ESP8266WiFi.h"
#include "ArduinoJson.h"
#include "FactorySensorManager.h"

DataManager::DataManager()
    : managers{
          FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_HUMIDITY,
          FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE,
          FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_PRESSURE,
          FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_TEMP,
          FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_HUMIDITY,
          FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_VOLTAJE,
          FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_TEMPERATURE,
          FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_STATUS,
          FactorySensorManager::TYPE_SENSOR_MANAGER::PANEL_VOLTAJE,
          FactorySensorManager::TYPE_SENSOR_MANAGER::ULTRAVIOLE_INDEX,
          FactorySensorManager::TYPE_SENSOR_MANAGER::BRIGHTNESS,
          FactorySensorManager::TYPE_SENSOR_MANAGER::VOLATILE_ORGANIC_COMPUNDS,
          FactorySensorManager::TYPE_SENSOR_MANAGER::EPOCH} {
  this->m_factoryManager = new FactorySensorManager();
  for (size_t manager = 0; manager < MANAGER_SIZE; manager++) {
    this->variables[manager] = -1;
  }
}

DataManager::~DataManager() {}

void DataManager::getVariableData() {
  SensorManager *m_sensorManager;
  for (int manager = 0; manager < MANAGER_SIZE; manager++) {
    m_sensorManager = m_factoryManager->createManager(this->managers[manager]);
    m_sensorManager->getCleanedData([&](long data) -> void { variables[manager] = data; });
    delete m_sensorManager;
  }
  yield();
}

String DataManager::getPayload() {
  getVariableData();

  const size_t capacity = JSON_OBJECT_SIZE(10);
  
  DynamicJsonDocument doc(capacity);

  doc["t"]             = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE];
  doc["h"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_HUMIDITY];
  doc["sH"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_HUMIDITY];
  // doc["pressure"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_PRESSURE];
  doc["u"]                      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::ULTRAVIOLE_INDEX];
  doc["b"]              = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BRIGHTNESS];
  doc["sT"]        = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_TEMP];
  doc["v"]           = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::VOLATILE_ORGANIC_COMPUNDS];
  // doc["panelvoltaje"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::PANEL_VOLTAJE];
  doc["timestamp"]               = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::EPOCH];

  doc["la"]            = "10.399080";
  doc["lo"]           = "-75.504142";

  // doc["bV"]          = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_VOLTAJE];
  // doc["bT"]      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_TEMPERATURE];

  serializeJson(doc, this->json_array);

  return json_array;
}
