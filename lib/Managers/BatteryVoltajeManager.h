///////////////////////////////////////////////////////////
//  BatteryVoltajeManager.h
//  Implementation of the Class BatteryVoltajeManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_9C5C0B8D_638C_4425_9863_098FE76689FD__INCLUDED_)
#define EA_9C5C0B8D_638C_4425_9863_098FE76689FD__INCLUDED_

#include "SensorManager.h"

class BatteryVoltajeManager : public SensorManager
{

public:
	BatteryVoltajeManager();
	virtual ~BatteryVoltajeManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_9C5C0B8D_638C_4425_9863_098FE76689FD__INCLUDED_)
