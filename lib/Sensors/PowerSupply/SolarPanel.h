///////////////////////////////////////////////////////////
//  SolarPanel.h
//  Implementation of the Class SolarPanel
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_)
#define EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_

#include "PCF8591.h"

class SolarPanel
{

public:
	SolarPanel();
	virtual ~SolarPanel();

	int SolarPanel(PCF8591 pcf8591);
	float getVoltaje();

};
#endif // !defined(EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_)
