///////////////////////////////////////////////////////////
//  CapacitiveSoilMoisture.h
//  Implementation of the Class CapacitiveSoilMoisture
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_)
#define EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_

#include "PCF8591.h"
#include "Sensor.h"
#include "Analog.h"

class CapacitiveSoilMoisture : public Sensor, public Analog
{

public:
	CapacitiveSoilMoisture();
	virtual ~CapacitiveSoilMoisture();
	CapacitiveSoilMoisture *m_CapacitiveSoilMoisture;

	CapacitiveSoilMoisture(PCF8591 *pcf8591);
	float getData();
	Sensor getInstance();

};
#endif // !defined(EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_)
