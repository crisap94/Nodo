///////////////////////////////////////////////////////////
//  SoilTempManager.h
//  Implementation of the Class SoilTempManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_7DAEB1F8_E6A5_41b9_87ED_7E1729D2F294__INCLUDED_)
#define EA_7DAEB1F8_E6A5_41b9_87ED_7E1729D2F294__INCLUDED_

#include "SensorManager.h"

class SoilTempManager : public SensorManager
{

public:
	SoilTempManager();
	virtual ~SoilTempManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_7DAEB1F8_E6A5_41b9_87ED_7E1729D2F294__INCLUDED_)
