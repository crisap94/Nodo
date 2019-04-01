///////////////////////////////////////////////////////////
//  ConfigManager.cpp
//  Implementation of the Class ConfigManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "ConfigManager.h"

#include "ESP8266WiFi.h"

#include <ArduinoJson.h>

#include "FS.h"

ConfigManager::ConfigManager() { this->http = new HTTPClient(); }

ConfigManager::~ConfigManager() {}

void ConfigManager::connectGPSServer() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");
  }
  Serial.println("Conneced");
  Serial.println("Local IP" + WiFi.localIP().toString());
  Serial.println("Gateway IP" + WiFi.gatewayIP().toString());
}

void ConfigManager::getInitialConfigData() {
  String url = "http://" + WiFi.gatewayIP().toString();

  this->http->begin(url);

  int httpCode = this->http->GET();
  String payload;
  if (httpCode == 0) { // Check the returning code

    payload = this->http->getString();
    Serial.println(payload); // Print the response payload
  }

  this->http->end();

  const size_t capacity =
      JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6) + 110;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, payload.c_str());

  const char *zoneId = doc["zoneId"]; // "asdasdasdasdasdsadasd"
  const char *topic = doc["topic"];   // "1234"

  float gps_lat = doc["gps"]["lat"]; // 12.123123
  float gps_lon = doc["gps"]["lon"]; // 23.123123

  JsonObject time = doc["time"];
  int time_year = time["year"];     // 1234
  int time_month = time["month"];   // 12
  int time_day = time["day"];       // 12
  int time_hour = time["hour"];     // 23
  int time_minute = time["minute"]; // 12
  int time_second = time["second"]; // 12

  if (gps_lat != 0 && gps_lon != 0) {
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println(
          "Error al abrir el archivo de configuración para escribir");
    }
    serializeJson(doc, configFile);
    reset();
  }
}

bool ConfigManager::isConfig() {
  if (!SPIFFS.begin()) {
    Serial.println("Error al montar el sistema de archivos");
    return false;
  }

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  return true;
}

void ConfigManager::reset() {
  Serial.println("Reiniciando Sistema");
  ESP.reset();
}
