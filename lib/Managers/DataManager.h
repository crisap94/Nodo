///////////////////////////////////////////////////////////
//  DataManager.h
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
#define EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_

#include "FactorySensorManager.h"

class DataManager {

public:
  DataManager();
  virtual ~DataManager();
  void getPayload(char *payload[700]);
  void getVariableData();

      private : struct Variables
  {
    float ambientHumidity = 0;
    float ambientTemperature = 0;
    float ambientPressure = 0;
    float battStatus = 0;
    float battTemperature = 0;
    float battVoltaje = 0;
    float ambientBrightness = 0;
    long epoch = 0;
    float panelVoltaje = 0;
    float soilHumidity = 0;
    float soilTemperature = 0;
    float ambientUv = 0;
    float ambientVoc = 0;
  };
  Variables *data;
  FactorySensorManager::TYPE_SENSOR_MANAGER managers[13];
  FactorySensorManager *m_factoryManager;
};
#endif // !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
