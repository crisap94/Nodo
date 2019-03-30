///////////////////////////////////////////////////////////
//  BatteryTemperatureManager.h
//  Implementation of the Class BatteryTemperatureManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_)
#define EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_

#include "SensorManager.h"
#include "PowerSupplyManager.h"
class BatteryTemperatureManager : public SensorManager {
private:
  float getValue() {
    PowerSupplyManager *ps = new PowerSupplyManager();
    bool temp = ps->m_battery->getTemp();
    delete ps;
    return temp;
  }

public:
  BatteryTemperatureManager();
  virtual ~BatteryTemperatureManager();
};
#endif // !defined(EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_)
