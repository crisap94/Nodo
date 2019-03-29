///////////////////////////////////////////////////////////
//  SolarPanelVoltajeManager.h
//  Implementation of the Class SolarPanelVoltajeManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_)
#define EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_

#include "SensorManager.h"

class SolarPanelVoltajeManager : public SensorManager
{

public:
	SolarPanelVoltajeManager();
	virtual ~SolarPanelVoltajeManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_)
