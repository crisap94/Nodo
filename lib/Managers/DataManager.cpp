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

void DataManager::getPayload() {
  getVariableData();

  const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(13);
  DynamicJsonDocument doc(capacity);

  JsonObject data = doc.createNestedObject("data");
  data["te"]             = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE];
  data["h"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_HUMIDITY];
  data["sH"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_HUMIDITY];
  data["p"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_PRESSURE];
  data["u"]                      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::ULTRAVIOLE_INDEX];
  data["b"]              = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BRIGHTNESS];
  data["sT"]        = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_TEMP];
  data["v"]           = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::VOLATILE_ORGANIC_COMPUNDS];
  data["pV"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::PANEL_VOLTAJE];
  data["ti"]               = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::EPOCH];

  JsonObject data_gps = data.createNestedObject("gps");
  data_gps["lat"]            = "10.399080";
  data_gps["lon"]           = "-75.504142";

  data["bV"]          = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_VOLTAJE];
  data["bT"]      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_TEMPERATURE];

  doc["zI"]                   = "5ac012583e194204e0afef6b";
  doc["fV"]          = "V1.0";

  JsonObject config = doc.createNestedObject("conf");
  config["m"]                   = "24-EC-64-A1-A7-C4";
  config["r"]                  = "-67";
  config["c"]               = 13;
  
  serializeJson(doc, this->json_array);
  // Serial.println("Generando JSON");
}

String DataManager::getJSON(){
  getPayload();

  return json_array;
} 