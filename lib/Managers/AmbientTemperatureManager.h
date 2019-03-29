///////////////////////////////////////////////////////////
//  AmbientTemperatureManager.h
//  Implementation of the Class AmbientTemperatureManager
//  Created on:      28-Mar-2019 4:29:31 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_91FC7453_B35D_40f2_9F99_843A3DC23E5A__INCLUDED_)
#define EA_91FC7453_B35D_40f2_9F99_843A3DC23E5A__INCLUDED_

#include "SensorManager.h"

class AmbientTemperatureManager : public SensorManager
{

public:
	AmbientTemperatureManager();
	virtual ~AmbientTemperatureManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_91FC7453_B35D_40f2_9F99_843A3DC23E5A__INCLUDED_)
