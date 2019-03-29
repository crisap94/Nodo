///////////////////////////////////////////////////////////
//  SoilMoistureManager.h
//  Implementation of the Class SoilMoistureManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_088A5508_F756_464c_A1D8_5F1A49FC14D7__INCLUDED_)
#define EA_088A5508_F756_464c_A1D8_5F1A49FC14D7__INCLUDED_

#include "SensorManager.h"

class SoilMoistureManager : public SensorManager
{

public:
	SoilMoistureManager();
	virtual ~SoilMoistureManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_088A5508_F756_464c_A1D8_5F1A49FC14D7__INCLUDED_)
