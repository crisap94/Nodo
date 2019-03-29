///////////////////////////////////////////////////////////
//  DS3231.h
//  Implementation of the Class DS3231
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_)
#define EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_

#include "Sensor.h"
#include "I2C.h"

class DS3231 : public Sensor, public I2C
{

public:
	DS3231();
	virtual ~DS3231();
	DS3231 *m_DS3231;

	inline void begin(){

	}
	void getData();
	Sensor getInstance();

};
#endif // !defined(EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_)
