///////////////////////////////////////////////////////////
//  RelativeHumidityManager.h
//  Implementation of the Class RelativeHumidityManager
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_)
#define EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_

#include "SensorManager.h"

class RelativeHumidityManager : public SensorManager
{

public:
	RelativeHumidityManager();
	virtual ~RelativeHumidityManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_3B18B229_E80A_4713_9940_14738F496D33__INCLUDED_)
