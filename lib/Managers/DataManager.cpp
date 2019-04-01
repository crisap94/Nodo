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

#include "FS.h"

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

  loadConfig();
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
  data["temperature"]             = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_TEMPERATURE];
  data["humidity"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_HUMIDITY];
  data["soilHumidity"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_HUMIDITY];
  data["pressure"]                = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::AMBIENT_PRESSURE];
  data["uv"]                      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::ULTRAVIOLE_INDEX];
  data["brightness"]              = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BRIGHTNESS];
  data["floorTemperature"]        = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::SOIL_TEMP];
  data["volatileGases"]           = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::VOLATILE_ORGANIC_COMPUNDS];
  data["panelvoltaje"]            = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::PANEL_VOLTAJE];
  data["timestamp"]               = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::EPOCH];

  JsonObject data_gps = data.createNestedObject("gps");
  data_gps["latitude"]            = this->lat;
  data_gps["longitude"]           = this->lon;

  data["batteryVoltaje"]          = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_VOLTAJE];
  data["batteryTmeperature"]      = this->variables[FactorySensorManager::TYPE_SENSOR_MANAGER::BATT_TEMPERATURE];

  doc["zoneId"]                   = this->zoneId;
  doc["firmwareVersion"]          = "V1.0";

  JsonObject config = doc.createNestedObject("config");
  config["mac"]                   = WiFi.macAddress();
  config["rssi"]                  = WiFi.RSSI(0);
  config["channel"]               = WiFi.channel();

  serializeJson(doc, this->json_array);

}

String DataManager::getJSON(){
  getPayload();

  return json_array;
} 

void DataManager::loadConfig(){
  File configFile = SPIFFS.open("/config.json", "r");

  size_t size = configFile.size();


  // Asigne un buffer para almacenar el contenido del archivo.
  std::unique_ptr<char[]> buf(new char[size]);

  // No usamos String aquí porque la biblioteca ArduinoJson requiere la entrada
  // buffer para ser mutable Si no usas ArduinoJson, también puedes
  // use configFile.readString en su lugar.
  configFile.readBytes(buf.get(), size);

  const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6) + 110;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, buf.get());

  const char *zoneid = doc["zoneId"]; // "asdasdasdasdasdsadasd"
  const char *topic = doc["topic"];   // "1234"

  this->zoneId = String(zoneid);
  this->topic = String(topic);

   this->lat = doc["gps"]["lat"]; // 12.123123
   this->lon = doc["gps"]["lon"]; // 23.123123

  JsonObject time = doc["time"];
  int time_hour = time["hour"];     // 23
  int time_minute = time["minute"]; // 12
  int time_second = time["second"]; // 12
  int time_year = time["year"];     // 1234
  int time_month = time["month"];   // 12
  int time_day = time["day"];       // 12

  this->m_now = new RtcDateTime(time_year,time_month,time_day,time_hour,time_minute,time_second);
}