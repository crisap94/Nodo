///////////////////////////////////////////////////////////
//  UltraVioletIndexManager.h
//  Implementation of the Class UltraVioletIndexManager
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_)
#define EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_

#include "SensorManager.h"
#include "VEML6075.h"
class UltraVioletIndexManager : public SensorManager
{
  private:
	float getValue() { return VEML6075::getInstance()->getValue() ;}

  public:
	UltraVioletIndexManager();
	virtual ~UltraVioletIndexManager();

};
#endif // !defined(EA_A9BFB58B_09E9_4dd0_8654_9836D3FC2C91__INCLUDED_)
