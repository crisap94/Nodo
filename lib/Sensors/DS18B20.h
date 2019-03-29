///////////////////////////////////////////////////////////
//  DS18B20.h
//  Implementation of the Class DS18B20
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_)
#define EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_

#include "Sensor.h"
#include "OneWire.h"

class DS18B20 : public Sensor, public OneWire
{

public:
	DS18B20();
	virtual ~DS18B20();
	DS18B20 *m_DS18B20;

	void begin();
	void getData();
	Sensor getInstance();

};
#endif // !defined(EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_)
