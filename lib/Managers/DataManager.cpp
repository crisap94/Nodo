///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DataManager.h"

#include "ArduinoJson.h"

#include "FS.h"

#include <Scheduller.hpp>

DataManager::DataManager()

    : managers{ManagerType::AMBIENT_HUMIDITY,
               ManagerType::AMBIENT_TEMPERATURE,
               ManagerType::AMBIENT_PRESSURE,
               ManagerType::SOIL_TEMP,
               ManagerType::SOIL_HUMIDITY,
               ManagerType::BATT_VOLTAJE,
               ManagerType::BATT_TEMPERATURE,
               //ManagerType::BATT_STATUS,
               ManagerType::PANEL_VOLTAJE,
               ManagerType::ULTRAVIOLE_INDEX,
               ManagerType::BRIGHTNESS,
               ManagerType::VOLATILE_ORGANIC_COMPUNDS,
               //ManagerType::EPOCH
               },
      intervals{Interval::INTERVAL_AMBIENT_HUMIDITY,
                Interval::INTERVAL_AMBIENT_PRESSURE,
                Interval::INTERVAL_AMBIENT_PRESSURE,
                Interval::INTERVAL_SOIL_TEMP,
                Interval::INTERVAL_SOIL_HUMIDITY,
                Interval::INTERVAL_BATT_VOLTAJE,
                Interval::INTERVAL_BATT_TEMPERATURE,
                //Interval::INTERVAL_BATT_STATUS,
                Interval::INTERVAL_PANEL_VOLTAJE,
                Interval::INTERVAL_ULTRAVIOLE_INDEX,
                Interval::INTERVAL_BRIGHTNESS,
                Interval::INTERVAL_VOLATILE_ORGANIC_COMPUNDS,
                //Interval::INTERVAL_EPOCH
                },
      algorithm{Algorithm::ALGORITHM_AMBIENT_HUMIDITY,
                Algorithm::ALGORITHM_AMBIENT_PRESSURE,
                Algorithm::ALGORITHM_AMBIENT_PRESSURE,
                Algorithm::ALGORITHM_SOIL_TEMP,
                Algorithm::ALGORITHM_SOIL_HUMIDITY,
                Algorithm::ALGORITHM_BATT_VOLTAJE,
                Algorithm::ALGORITHM_BATT_TEMPERATURE,
                //Algorithm::ALGORITHM_BATT_STATUS,
                Algorithm::ALGORITHM_PANEL_VOLTAJE,
                Algorithm::ALGORITHM_ULTRAVIOLE_INDEX,
                Algorithm::ALGORITHM_BRIGHTNESS,
                Algorithm::ALGORITHM_VOLATILE_ORGANIC_COMPUNDS,
                //Algorithm::ALGORITHM_EPOCH
                } {

  Serial.println("\n\nDATA MANAGER -> Starting Factory Manager");

  m_factoryManager = new FactorySensorManager();

  tMain =
      new Task(TASK_SECOND, TASK_FOREVER, mainFunction, m_dataScheduler, false);

  Serial.println("DATA MANAGER -> Setting to NOT_SET all the Variables");
  for (size_t manager = 0; manager < MANAGER_SIZE; manager++) {
    variables[manager] = NOT_SET;
  }

  Serial.println("DATA MANAGER -> Setting the matrix of Raw Values to NOT_SET");
  for (size_t managerData = 0; managerData < MANAGER_SIZE; managerData++) {
    for (size_t sample = 0; sample < SAMPLES; sample++) {
      rawValues[managerData][sample] = NOT_SET;
    }
  }

  Serial.println("DATA MANAGER -> Copying Scheduller");
  m_dataScheduler = &scheduller;

  for (size_t task = 0; task < MANAGER_SIZE; task++) {
    Serial.printf("DATA MANAGER -> Creating Task (%s)\n",
                  MANAGER_TYPE(managers[task]).c_str());
    m_tasks[task] = new Task(
        TASK_MILLISECOND * intervals[task], TASK_FOREVER,
        [this, task]() {

          uint8_t dataset = task;

          /**
           * @brief Verify if the corresponding dataset of values has
           * any missing sample like NOT_SET, which mean the value has
           * not been taken.
           */
          for (size_t sample = 0; sample < SAMPLES; sample++) {
            if (rawValues[dataset][sample] == NOT_SET) {
              /**
               * @brief once the sample is found, create the
               * corresponding manager to get only 1 value
               * that corresponds to the dataset
               *
               */

              ManagerType type = (ManagerType)managers[task];

              SensorManager *manager;
              manager = m_factoryManager->createManager(type);
              this->rawValues[dataset][sample] = manager->getData();

              Serial.printf("DATA MANAGER -> Gettin Value from (%s) -> \t\t\t(%.1f)\n",
                            MANAGER_TYPE(managers[task]).c_str(),
                            this->rawValues[dataset][sample]);

              delete manager;

              break;

            } else if (sample == (SAMPLES - 1)) {

              Serial.printf("\n\nDATA MANAGER -> Disabling task (%s)\n\n",
                            MANAGER_TYPE(managers[task]).c_str());
              /**
               * @brief if all the data are already gathered then
               * the task is disabled
               *
               */
              this->m_tasks[task]->disable();

              /**
               * @brief After
               *
               */
              m_cleaner = new DataCleaner<long>;
              m_cleaner->begin(algorithm[task], SAMPLES);
              for (size_t sample = 0; sample < SAMPLES; sample++) {
                m_cleaner->add(rawValues[task][sample]);
              }
              variables[task] = m_cleaner->get();
              Serial.printf("DATA MANAGER -> Updating average value for (%s)(%.1f)\n\n",
                            MANAGER_TYPE(managers[task]).c_str(),
                            variables[task]);
              delete m_cleaner;
            }
          }
        },
        m_dataScheduler);
  }

  mainFunction = [this]() {
    loadConfig();
    for (size_t task = 0; task < MANAGER_SIZE; task++) {
      // Enable all the Tasks previusly added to thescheduller
      Serial.printf("\nDATA MANAGER -> Enabling task (%s)\n\n",
                    MANAGER_TYPE(managers[task]).c_str());
                    
      if (managers[task] == ManagerType::VOLATILE_ORGANIC_COMPUNDS) {
        this->m_tasks[task]->enableDelayed(5000);
      } else {
        m_tasks[task]->enable();
      }
    }

  };
}

DataManager::~DataManager() {}

bool DataManager::isReady() {
  for (size_t variable = 0; variable < MANAGER_SIZE; variable++) {
    if (variables[variable] == NOT_SET) {
      return false;
    }
  }
  return true;
}

String DataManager::getPayload() {

  if (isReady()) {
    SensorManager *m_rtc = m_factoryManager->createManager(ManagerType::EPOCH);
    SensorManager *m_bStatus =
        m_factoryManager->createManager(ManagerType::BATT_STATUS);

    uint64_t EPOCH = m_rtc->getData();
    bool battStatus = m_bStatus->getData();

    delete m_bStatus;
    delete m_rtc;

    const size_t capacity = JSON_OBJECT_SIZE(15);
    DynamicJsonDocument doc(capacity);

    doc["t"] = variables[VARIABLES::VAR_AMBIENT_TEMPERATURE];
    doc["h"] = variables[VARIABLES::VAR_AMBIENT_HUMIDITY];
    doc["sH"] = variables[VARIABLES::VAR_SOIL_HUMIDITY];
    doc["p"] = variables[VARIABLES::VAR_AMBIENT_PRESSURE];
    doc["u"] = variables[VARIABLES::VAR_ULTRAVIOLE_INDEX];
    doc["b"] = variables[VARIABLES::VAR_BRIGHTNESS];
    doc["sT"] = variables[VARIABLES::VAR_SOIL_TEMP];
    doc["v"] = variables[VARIABLES::VAR_VOLATILE_ORGANIC_COMPUNDS];
    doc["pV"] = variables[VARIABLES::VAR_PANEL_VOLTAJE];
    doc["ti"] = EPOCH;
    doc["la"] = lat;
    doc["lo"] = lon;
    doc["bV"] = variables[VARIABLES::VAR_BATT_VOLTAJE];
    doc["bT"] = variables[VARIABLES::VAR_BATT_TEMPERATURE];
    doc["bS"] = battStatus;

    String json_array;

    serializeJsonPretty(doc, json_array);

    resetValues();

    return json_array;
  }

  return "The Payload is not ready yet";
}

void DataManager::resetValues() {
  for (size_t dataset = 0; dataset < MANAGER_SIZE; dataset++) {
    variables[dataset] = NOT_SET;
    for (size_t sample = 0; sample < SAMPLES; sample++) {
      rawValues[dataset][sample] = NOT_SET;
    }
  }
}

void DataManager::loadConfig() {
  if (!SPIFFS.begin()) {
    Serial.println(F("DATA MANAGER -> Error mounting File system"));
  }
  Serial.println(F("DATA MANAGER -> Success on mounting the File system"));

  File file = SPIFFS.open("/config.json", "r");

  const size_t capacity = 256;
  DynamicJsonDocument doc(capacity);


  DeserializationError error = deserializeJson(doc, file);

  //serializeJsonPretty(doc,Serial);

  Serial.printf("\nJson Error: %s\n",error.c_str());

  lon = doc["latitud"];  // 10.12312312
  lat = doc["longitud"]; // -90.12312312
  refresh = doc["refreshWindow"];

  Serial.println(F("DATA MANAGER -> Setting latitud and Longitud"));
  Serial.print(F("Latitud:"));
  Serial.println(lat,10);
  Serial.print(F("Longitud:"));
  Serial.println(lon,10);
  Serial.print(F("Refresh Window:"));
  Serial.println(refresh);

  file.close();

  SPIFFS.end();
}