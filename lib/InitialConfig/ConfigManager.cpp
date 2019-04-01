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
  Serial.println("Local IP" + String(WiFi.localIP()));
  Serial.println("Gateway IP" + String(WiFi.gatewayIP()));
}

void ConfigManager::getInitialConfigData() {
  String url = "http://" + String(WiFi.gatewayIP());

  this->http->begin(url);

  int httpCode = this->http->GET();
  String payload;
  if (httpCode == 0) { // Check the returning code

    payload =  this->http->getString(); 
    Serial.println(payload);     // Print the response payload
  }

  this->http->end();

  const size_t capacity = 2 * JSON_OBJECT_SIZE(2) + 50;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, payload.c_str());

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Error al abrir el archivo de configuración para escribir");
  }
  serializeJson(doc, configFile);
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
