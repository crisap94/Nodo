///////////////////////////////////////////////////////////
//  NTC.h
//  Implementation of the Class NTC
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
#define EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_

#include "Sensor.h"
#include "PCF8591.h"
#include "Analog.h"

class NTC : public Analog, public Sensor
{

public:
	NTC();
	virtual ~NTC();
	NTC *m_NTC;

	NTC(PCF8591 pcf8591);
	float getData();
	Sensor getInstance();

};
#endif // !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
