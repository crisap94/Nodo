///////////////////////////////////////////////////////////
//  BatteryStatusManager.h
//  Implementation of the Class BatteryStatusManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_095E038F_1A20_4263_8C6C_645FD1958410__INCLUDED_)
#define EA_095E038F_1A20_4263_8C6C_645FD1958410__INCLUDED_

#include "PowerSupplyManager.h"
#include "SensorManager.h"

class BatteryStatusManager : public SensorManager {
private:
  float getValue() {
    PowerSupplyManager *ps = new PowerSupplyManager();
	bool status = ps->m_battery->getStatus();
	delete ps;
	return status;
  }

public:
  BatteryStatusManager();
  virtual ~BatteryStatusManager();
};
#endif // !defined(EA_095E038F_1A20_4263_8C6C_645FD1958410__INCLUDED_)
