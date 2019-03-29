///////////////////////////////////////////////////////////
//  RT9013.h
//  Implementation of the Class RT9013
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_)
#define EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_

#include "PCF8574.h"
#include "Digital.h"

class RT9013 : public Digital
{

public:
	RT9013();
	virtual ~RT9013();

	RT9013(PCF8574 pcf8574);
	int turnOff();
	int turnOn();

};
#endif // !defined(EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_)
