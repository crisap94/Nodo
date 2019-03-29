///////////////////////////////////////////////////////////
//  Battery.h
//  Implementation of the Class Battery
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_)
#define EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_

#include "PCF8591.h"
#include "TP4056.h"

class Battery
{

public:
	Battery();
	virtual ~Battery();
	TP4056 *m_TP4056;

	Battery(PCF8591 pcf8591);
	float getTemp();
	float getVoltaje();

};
#endif // !defined(EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_)
