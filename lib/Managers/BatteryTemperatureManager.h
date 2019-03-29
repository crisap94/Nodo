///////////////////////////////////////////////////////////
//  BatteryTemperatureManager.h
//  Implementation of the Class BatteryTemperatureManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_)
#define EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_

#include "SensorManager.h"

class BatteryTemperatureManager : public SensorManager
{

public:
	BatteryTemperatureManager();
	virtual ~BatteryTemperatureManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_007B0A38_6270_4e01_81F3_1F29D846DBF9__INCLUDED_)
