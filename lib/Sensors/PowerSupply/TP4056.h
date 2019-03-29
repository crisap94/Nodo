///////////////////////////////////////////////////////////
//  TP4056.h
//  Implementation of the Class TP4056
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_)
#define EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_

#include "PCF8574.h"
#include "Digital.h"

class TP4056 : public Digital
{

public:
	TP4056();
	virtual ~TP4056();

	TP4056(PCF8574 pcf8574);
	boolean checkBatt();
	int turnOff();
	int turnOn();

};
#endif // !defined(EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_)
