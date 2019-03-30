///////////////////////////////////////////////////////////
//  DataManager.h
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
#define EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_

#include "FactorySensorManager.h"
#include "ArduinoJson.h"

class DataManager {

public:
  DataManager();
  virtual ~DataManager();
  const char* getPayload();

private:
  int managers[13];
  FactorySensorManager factoryManager;
};
#endif // !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
