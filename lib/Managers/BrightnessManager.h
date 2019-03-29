///////////////////////////////////////////////////////////
//  BrightnessManager.h
//  Implementation of the Class BrightnessManager
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_4C6157B0_482A_4599_B030_A5B6AED6E71A__INCLUDED_)
#define EA_4C6157B0_482A_4599_B030_A5B6AED6E71A__INCLUDED_

#include "SensorManager.h"

class BrightnessManager : public SensorManager
{

public:
	BrightnessManager();
	virtual ~BrightnessManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_4C6157B0_482A_4599_B030_A5B6AED6E71A__INCLUDED_)
