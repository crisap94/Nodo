///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DataManager.h"

#include "ArduinoJson.h"

DataManager::DataManager()

    : managers{ManagerType::AMBIENT_HUMIDITY,
               ManagerType::AMBIENT_TEMPERATURE,
               ManagerType::AMBIENT_PRESSURE,
               ManagerType::SOIL_TEMP,
               ManagerType::SOIL_HUMIDITY,
               ManagerType::BATT_VOLTAJE,
               ManagerType::BATT_TEMPERATURE,
               ManagerType::BATT_STATUS,
               ManagerType::PANEL_VOLTAJE,
               ManagerType::ULTRAVIOLE_INDEX,
               ManagerType::BRIGHTNESS,
               ManagerType::VOLATILE_ORGANIC_COMPUNDS,
               ManagerType::EPOCH},
      intervals{Interval::INTERVAL_AMBIENT_HUMIDITY,
                Interval::INTERVAL_AMBIENT_PRESSURE,
                Interval::INTERVAL_AMBIENT_PRESSURE,
                Interval::INTERVAL_SOIL_TEMP,
                Interval::INTERVAL_SOIL_HUMIDITY,
                Interval::INTERVAL_BATT_VOLTAJE,
                Interval::INTERVAL_BATT_TEMPERATURE,
                Interval::INTERVAL_BATT_STATUS,
                Interval::INTERVAL_PANEL_VOLTAJE,
                Interval::INTERVAL_ULTRAVIOLE_INDEX,
                Interval::INTERVAL_BRIGHTNESS,
                Interval::INTERVAL_VOLATILE_ORGANIC_COMPUNDS,
                Interval::INTERVAL_EPOCH},
      algorithm{Algorithm::ALGORITHM_AMBIENT_HUMIDITY,
                Algorithm::ALGORITHM_AMBIENT_PRESSURE,
                Algorithm::ALGORITHM_AMBIENT_PRESSURE,
                Algorithm::ALGORITHM_SOIL_TEMP,
                Algorithm::ALGORITHM_SOIL_HUMIDITY,
                Algorithm::ALGORITHM_BATT_VOLTAJE,
                Algorithm::ALGORITHM_BATT_TEMPERATURE,
                Algorithm::ALGORITHM_BATT_STATUS,
                Algorithm::ALGORITHM_PANEL_VOLTAJE,
                Algorithm::ALGORITHM_ULTRAVIOLE_INDEX,
                Algorithm::ALGORITHM_BRIGHTNESS,
                Algorithm::ALGORITHM_VOLATILE_ORGANIC_COMPUNDS,
                Algorithm::ALGORITHM_EPOCH} {

  Serial.println("DEBUG -> Starting Factory Manager");

  m_factoryManager = new FactorySensorManager();

  Serial.println("DEBUG -> Setting to NOT_SET all the Variables");
  for (size_t manager = 0; manager < MANAGER_SIZE; manager++) {
    variables[manager] = NOT_SET;
  }

  Serial.println("DEBUG -> Setting the matrix of Raw Values to NOT_SET");
  for (size_t managerData = 0; managerData < MANAGER_SIZE; managerData++) {
    for (size_t sample = 0; sample < SAMPLES; sample++) {
      rawValues[managerData][sample] = NOT_SET;
    }
  }

  Serial.println("DEBUG -> Creating Scheduller");
  m_dataScheduler = new Scheduler();

  for (size_t task = 0; task < MANAGER_SIZE; task++) {
    Serial.printf("DEBUG -> Creating Task (%s)\n", MANAGER_TYPE(task).c_str());
    m_tasks[task] =
        new Task(TASK_MILLISECOND * intervals[task], TASK_FOREVER,
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

                       ManagerType type = (ManagerType)task;
                       SensorManager *manager;
                       manager = m_factoryManager->createManager(type);
                       this->rawValues[dataset][sample] = manager->getData();

                       Serial.printf("Gettin Value from (%s) -> \t\t\t(%d)\n",
                                     MANAGER_TYPE(task).c_str(),
                                     this->rawValues[dataset][sample]);

                       delete manager;

                       break;

                     } else if (sample == (SAMPLES - 1)) {

                       Serial.printf("\n\nDisabling task (%s)\n\n",
                                     MANAGER_TYPE(task).c_str());
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
                       Serial.printf("Updating average value for (%s)\n\n",
                                     MANAGER_TYPE(task).c_str());
                       m_cleaner = new DataCleaner<long>;
                       m_cleaner->begin(algorithm[task], SAMPLES);
                       for (size_t sample = 0; sample < SAMPLES; sample++) {
                         m_cleaner->add(rawValues[task][sample]);
                       }
                       variables[task] = m_cleaner->get();
                       delete m_cleaner;
                     }
                   }
                 },
                 m_dataScheduler);
  }

  for (size_t task = 0; task < MANAGER_SIZE; task++) {
    // Enable all the Tasks previusly added to thescheduller
    m_tasks[task]->enable();
  }
}

DataManager::~DataManager() {}

bool DataManager::dataAvailable() {
  for (size_t dataset = 0; dataset < MANAGER_SIZE; dataset++) {
    for (size_t sample = 0; sample < SAMPLES; sample++) {
      if (rawValues[dataset][sample] == NOT_SET) {
        return false;
      }
    }
  }

  return true;
}

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
    const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) +
                            JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(13);
    DynamicJsonDocument doc(capacity);

    doc["t"] = variables[ManagerType::AMBIENT_TEMPERATURE];
    doc["h"] = variables[ManagerType::AMBIENT_HUMIDITY];
    doc["sH"] = variables[ManagerType::SOIL_HUMIDITY];
    doc["p"] = variables[ManagerType::AMBIENT_PRESSURE];
    doc["u"] = variables[ManagerType::ULTRAVIOLE_INDEX];
    doc["b"] = variables[ManagerType::BRIGHTNESS];
    doc["sT"] = variables[ManagerType::SOIL_TEMP];
    doc["v"] = variables[ManagerType::VOLATILE_ORGANIC_COMPUNDS];
    doc["pV"] = variables[ManagerType::PANEL_VOLTAJE];
    doc["ti"] = variables[ManagerType::EPOCH];
    doc["la"] = "10.399080";
    doc["lo"] = "-75.504142";
    doc["bV"] = variables[ManagerType::BATT_VOLTAJE];
    doc["bT"] = variables[ManagerType::BATT_TEMPERATURE];

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

void DataManager::loop() { m_dataScheduler->execute(); }
