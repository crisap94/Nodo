///////////////////////////////////////////////////////////
//  ConfigManager.cpp
//  Implementation of the Class ConfigManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "ConfigManager.h"

#include <ArduinoJson.h>

#include <Scheduller.hpp>

#include <DS3231.h>

#include "FS.h"

ConfigManager::ConfigManager() {

  response = "";

  Serial.println(F("\CONFIG MANAGER -> Creating Config task"));
  tConfig = new Task(TASK_SECOND, TASK_FOREVER, checkInitialConfig, &scheduller,
                     true);

  Serial.println(F("\CONFIG MANAGER -> Creating Connection task"));
  tConnect =
      new Task(TASK_SECOND, TASK_FOREVER, 0, &scheduller);

  Serial.println(F("CONFIG MANAGER -> Creating HTTP Client"));
  http = new HTTPClient();

  // Serial.println(F("CONFIG MANAGER -> Enabling Config Task"));
  // tConnect->enable();
  // Serial.printf("CONFIG MANAGER -> Config task Enabled: %s",
  //               tConnect->isEnabled() ? "true" : "false");

  checkInitialConfig = [this]() {

    if (!SPIFFS.begin()) {
      Serial.println(F("CONFIG MANAGER -> Error mounting File system"));
      Serial.println(F("CONFIG MANAGER -> Rebooting Task"));
      return;
    }

    Serial.println(F("CONFIG MANAGER -> Success on mounting the File system"));

    File file = SPIFFS.open("/config.json", "r");

    const size_t capacity = 256;
    DynamicJsonDocument doc(capacity);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);

    Serial.printf("\nCONFIG MANAGER -> File parsing status: %s\n",
                  error.c_str());

    Serial.println(F("JSON:"));
    serializeJsonPretty(doc, Serial);

    if (error) {
      file.close();

      file = SPIFFS.open("/config.json", "w");

      Serial.println(F(
          "\nCONFIG MANAGER -> Failed to read file, creating default config"));

      const size_t capacity = 256;
      DynamicJsonDocument defaultDoc(capacity);

      defaultDoc["zoneId"] = config.zoneId;
      defaultDoc["epoch"] = config.epoch;
      defaultDoc["longitud"] = config.longitud;
      defaultDoc["latitud"] = config.latitud;
      defaultDoc["refreshWindow"] = config.refreshWindow;

      Serial.println(F("CONFIG MANAGER -> Initializing the /config.json File"));
      serializeJsonPretty(defaultDoc, Serial);
      serializeJson(defaultDoc, file);

      if (SpiffCounter == 10) {
        yield();
        SPIFFS.format();
        SpiffCounter = 0;
      }
      SpiffCounter++;

      file.close();
      Serial.println(F("\nCONFIG MANAGER -> Rebooting Task"));
      return;

    } else {

      if (!doc.containsKey("zoneId") || !doc.containsKey("epoch") ||
          !doc.containsKey("latitud") || !doc.containsKey("longitud") ||
          !doc.containsKey("refreshWindow")) {
        Serial.println(
            F("CONFIG MANAGER-> The stored JSON do not containg a valid file"));
        SPIFFS.format();
        file.close();
        end();
        Serial.println(F("CONFIG MANAGER -> Rebooting Task"));
        return;
      }

      file.close();

      strlcpy(config.zoneId, doc["zoneId"] | NOT_CONFIGURED,
              sizeof(config.zoneId));
      config.epoch = doc["epoch"];       // 123123123123123
      config.latitud = doc["latitud"];   // 10.12312312
      config.longitud = doc["longitud"]; // -90.12312312
      config.refreshWindow = doc["refreshWindow"];

      if (config.epoch == EPOCH_19_1_1 || config.latitud == NOT_SET ||
          config.longitud == NOT_SET) {
        Serial.println(F("\nCONFIG MANAGER -> The JSON file has the default "
                         "configuration"));
        Serial.println(
            F("\nCONFIG MANAGER -> Connecting to GPS Server to Get then new "
              "configuration"));

        tConnect->yield(connectToGPSServer);

      } else {

        // serializeJsonPretty(doc, Serial);
        end();

        /*  Serial.printf(
             "\n\nCONFIG MANAGER -> Task Config Manager Enabled? : %s\n",
             tConnect->isEnabled() ? "true" : "false"); */

        Serial.println(F("CONFIG MANAGER -> Disabling Task Config Manager "));

        configFlag = true;
        tConnect->disable();
      }
    }

  };

  connectToGPSServer = [this]() {
    Serial.print(F("CONFIG MANAGER -> "));
    Serial.print(millis());
    Serial.println(F(": connectToGPSServer."));
    Serial.println(F("CONFIG MANAGER -> WiFi parameters: "));
    Serial.print(F("CONFIG MANAGER -> SSID: "));
    Serial.println(ssid);
    Serial.print(F("CONFIG MANAGER -> PWD : "));
    Serial.println(password);

    WiFi.mode(WIFI_STA);
    String hostname = "node-" + ESP.getChipId();
    WiFi.hostname(hostname);
    WiFi.begin(ssid, password);
    yield();

    // This will pass control back to Scheduler and
    // then continue with connection checking
    tConnect->yield(connectCheck);
  };

  connectCheck = [this]() {
    Serial.print(F("CONFIG MANAGER -> "));
    Serial.print(millis());
    Serial.println(F(": connectCheck."));

    if (WiFi.status() == WL_CONNECTED) { // Connection established
      Serial.print(F("CONFIG MANAGER -> "));
      Serial.print(millis());
      Serial.print(F(": Connected to GPS Server. Local ip: "));
      Serial.println(WiFi.localIP());
      tConnect->yield(requestFromGPS);
    } else {
      // re-request connection every 10 seconds
      if (tConnect->getRunCounter() % 10 == 0) {
        Serial.print(F("CONFIG MANAGER -> "));
        Serial.print(millis());
        Serial.println(F(": Re-requesting connection to GPS..."));

        WiFi.disconnect(true);
        yield(); // This is an esp8266 standard yield to allow linux wifi stack
        // run
        String hostname = "esp8266" + ESP.getChipId();
        WiFi.hostname(hostname);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        yield(); // This is an esp8266 standard yield to allow linux wifi stack
                 // run
      }

      if (tConnect->getRunCounter() == CONNECT_TIMEOUT) { // Connection Timeout
        tConnect->getInternalStatusRequest()->signal(
            CONNECT_FAILED); // Signal unsuccessful completion
        tConnect->disable();
        Serial.print(F("CONFIG MANAGER -> "));
        Serial.print(millis());
        Serial.println(F(": connectOnDisable."));
        Serial.print(millis());
        Serial.println(F(": Unable to connect to GPS SERVER."));
      }
    }
  };

  requestFromGPS = [this]() {
    Serial.println(F("CONFIG MANAGER -> Requesting data from GPS Server"));

    // String url = "http://" + WiFi.gatewayIP().toString() + "/smava";
    // String url = "https://my-json-server.typicode.com/crisap94/Nodo";
    String url = "http://192.168.0.114:3000/smava";

    yield();

    http->begin(url);

    int httpCode = http->GET();
    Serial.printf("CONFIG MANAGER -> GPS request status: %i\n", httpCode);

    if (httpCode == 200) { // Check the returning code

      response = http->getString();
      const size_t capacity = 256;
      DynamicJsonDocument doc(capacity);

      deserializeJson(doc, response); // Print the response payload

      http->end();

      strlcpy(config.zoneId, doc["zoneId"] | NOT_CONFIGURED,
              sizeof(config.zoneId));
      config.epoch = doc["epoch"];                 // 123123123123123
      config.latitud = doc["latitud"];             // 10.12312312
      config.longitud = doc["longitud"];           // -90.12312312
      config.refreshWindow = doc["refreshWindow"]; // -90.12312312

      tConnect->yield(updateTime);
    } else {
      http->end();

      Serial.printf("Request Failed with status %i\n", httpCode);
      Serial.println(F("Requesting again the data in 2 seconds"));
      return;
    }

  };

  updateTime = [this]() {
    // DS3231 *_ds3231 = DS3231::getInstance();
    // yield();
    /**
     * @brief Configure the RTc with the EPOCH from the  GPS server
     * And compare
     *
     * TODO this have to call a method placed in the DS3231 with the new epoch
     *
     * ? Use the config object to get the data
     *
     * !this method wasn't implemented yet because need merge
     */

    Serial.println(F("CONFIG MANAGER -> Task succesfully executed"));

    tConnect->yield(saveConfig);
  };

  saveConfig = [this]() {

    const size_t capacity = 256;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, response);

    Serial.println(F("CONFIG MANAGER -> Processing response"));
    Serial.println(F("CONFIG MANAGER -> Response:\n"));

    serializeJsonPretty(doc, Serial);

    response = "";

    strlcpy(config.zoneId, doc["zoneId"] | NOT_CONFIGURED,
            sizeof(config.zoneId));
    config.epoch = doc["epoch"];                 // 123123123123123
    config.latitud = doc["latitud"];             // 10.12312312
    config.longitud = doc["longitud"];           // -90.12312312
    config.refreshWindow = doc["refreshWindow"]; // -90.12312312

    if (config.latitud != NOT_SET && config.longitud != NOT_SET &&
        config.epoch != EPOCH_19_1_1) {
      yield();
      File configFile = SPIFFS.open("/config.json", "w");
      if (!configFile) {
        Serial.println(F("CONFIG MANAGER -> Error al abrir el archivo de "
                         "configuración para escribir"));
        configFile.close();
      } else {

        Serial.println(F("\n\nCONFIG MANAGER -> Saving new configuration"));

        serializeJson(doc, configFile);
        serializeJsonPretty(doc, Serial);
        configFile.close();
        SPIFFS.end();

        configFlag = true;
        
        Serial.println("");
        WiFi.disconnect();
        
        tConnect->disable();
      }
    } else {

      tConnect->yield(requestFromGPS);
    }

  };
}

ConfigManager::~ConfigManager() {}

void ConfigManager::end() { SPIFFS.end(); }

void ConfigManager::reset() {

  Serial.println(F("\nReiniciando Sistema\n\n"));

  ESP.reset();
}
