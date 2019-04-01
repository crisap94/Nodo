///////////////////////////////////////////////////////////
//  DataManager.h
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
#define EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_

#include "FactorySensorManager.h"

#define MANAGER_SIZE 13

class DataManager {

public:
  DataManager();
  virtual ~DataManager();
  String getJSON();

private:
  void getPayload();
  String json_array;
  void getVariableData();
  long variables[MANAGER_SIZE];
  FactorySensorManager::TYPE_SENSOR_MANAGER managers[MANAGER_SIZE];
  FactorySensorManager *m_factoryManager;
};
#endif // !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
