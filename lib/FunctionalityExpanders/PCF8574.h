///////////////////////////////////////////////////////////
//  PCF8574.h
//  Implementation of the Class PCF8574
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_)
#define EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_

#include "I2C.h"
#include "Expander.h"

class PCF8574 : public I2C, public Expander
{

public:
	PCF8574();
	virtual ~PCF8574();
	PCF8574 *m_PCF8574;

	inline void begin(){

	}
	void getData();

};
#endif // !defined(EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_)
