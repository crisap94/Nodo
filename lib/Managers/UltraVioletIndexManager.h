///////////////////////////////////////////////////////////
//  UltraVioletIndexManager.h
//  Implementation of the Class UltraVioletIndexManager
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_)
#define EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_

#include "SensorManager.h"

class UltraVioletIndexManager : public SensorManager
{

public:
	UltraVioletIndexManager();
	virtual ~UltraVioletIndexManager();

	float getValue();
	float cleanData();

};
#endif // !defined(EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_)
