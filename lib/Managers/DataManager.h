///////////////////////////////////////////////////////////
//  DataManager.h
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
#define EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_

#include "FactorySensorManager.h"

#include "DataCleaner.h"

#define _TASK_STD_FUNCTION
#define _TASK_INLINE
#include <TaskScheduler.h>

#define MANAGER_SIZE 13
#define SAMPLES 10

#define NOT_SET -1
#define TASK_ENABLED true

#define MANAGER_TYPE(type)                                                     \
  this->m_factoryManager->getManagerType((ManagerType)type)

class DataManager {

public:

/**
 * @brief 
 * TODO Place the Intervals from the Document
 * 
 */
  enum VARIABLE_SENSING_INTERVAL{
    INTERVAL_AMBIENT_HUMIDITY            = 1500,
    INTERVAL_AMBIENT_TEMPERATURE         = 1000,
    INTERVAL_AMBIENT_PRESSURE            = 1000,
    INTERVAL_SOIL_TEMP                   = 100,
    INTERVAL_SOIL_HUMIDITY               = 100,
    INTERVAL_BATT_VOLTAJE                = 100,
    INTERVAL_BATT_TEMPERATURE            = 100,
    INTERVAL_BATT_STATUS                 = 10,
    INTERVAL_PANEL_VOLTAJE               = 100,
    INTERVAL_ULTRAVIOLE_INDEX            = 50,
    INTERVAL_BRIGHTNESS                  = 600,
    INTERVAL_VOLATILE_ORGANIC_COMPUNDS   = 1400,
    INTERVAL_EPOCH                       = 10,
  };

  enum SMOOTH_ALGORITHM{
    ALGORITHM_AMBIENT_HUMIDITY            = SMOOTHED_AVERAGE,
    ALGORITHM_AMBIENT_TEMPERATURE         = SMOOTHED_AVERAGE,
    ALGORITHM_AMBIENT_PRESSURE            = SMOOTHED_AVERAGE,
    ALGORITHM_SOIL_TEMP                   = SMOOTHED_AVERAGE,
    ALGORITHM_SOIL_HUMIDITY               = SMOOTHED_EXPONENTIAL,
    ALGORITHM_BATT_VOLTAJE                = SMOOTHED_EXPONENTIAL,
    ALGORITHM_BATT_TEMPERATURE            = SMOOTHED_EXPONENTIAL,
    ALGORITHM_BATT_STATUS                 = SMOOTHED_EXPONENTIAL,
    ALGORITHM_PANEL_VOLTAJE               = SMOOTHED_AVERAGE,
    ALGORITHM_ULTRAVIOLE_INDEX            = SMOOTHED_AVERAGE,
    ALGORITHM_BRIGHTNESS                  = SMOOTHED_AVERAGE,
    ALGORITHM_VOLATILE_ORGANIC_COMPUNDS   = SMOOTHED_EXPONENTIAL,
    ALGORITHM_EPOCH                       = SMOOTHED_AVERAGE,
  };

  String getPayload();
  bool isReady();

  void loop();
  
  DataManager();
  virtual ~DataManager();

private:

  typedef FactorySensorManager::TYPE_SENSOR_MANAGER ManagerType;
  typedef VARIABLE_SENSING_INTERVAL Interval;
  typedef  SMOOTH_ALGORITHM Algorithm;

  FactorySensorManager *m_factoryManager;
  DataCleaner<long> *m_cleaner;

  ManagerType managers[MANAGER_SIZE];
  uint16_t intervals[MANAGER_SIZE];
  uint16_t algorithm[MANAGER_SIZE];


  Scheduler *m_dataScheduler;
  Task *m_tasks[MANAGER_SIZE];

  long rawValues[MANAGER_SIZE][SAMPLES];

  long variables[MANAGER_SIZE];

  String json_array;

  bool dataAvailable();

  void resetValues();

};
#endif // !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
