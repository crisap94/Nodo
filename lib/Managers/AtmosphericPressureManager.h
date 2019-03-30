///////////////////////////////////////////////////////////
//  AtmosphericPressureManager.h
//  Implementation of the Class AtmosphericPressureManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_DC90C153_EF45_4f12_B3A3_5238C844D31B__INCLUDED_)
#define EA_DC90C153_EF45_4f12_B3A3_5238C844D31B__INCLUDED_

#include "BME680.h"
#include "SensorManager.h"

class AtmosphericPressureManager : public SensorManager {
private:
  float getData() { return BME680::getInstance()->getPressure(); }

public:
  AtmosphericPressureManager();
  virtual ~AtmosphericPressureManager();
  
};
#endif // !defined(EA_DC90C153_EF45_4f12_B3A3_5238C844D31B__INCLUDED_)
