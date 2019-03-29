///////////////////////////////////////////////////////////
//  VEML6030.h
//  Implementation of the Class VEML6030
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_315ED3C2_7FF3_40b6_BE9E_BA6558E289F0__INCLUDED_)
#define EA_315ED3C2_7FF3_40b6_BE9E_BA6558E289F0__INCLUDED_

#include "Sensor.h"
#include "I2C.h"

class VEML6030 : public Sensor, public I2C
{

public:
	VEML6030();
	virtual ~VEML6030();
	VEML6030 *m_VEML6030;

	void begin();
	void getData();
	Sensor getInstance();

};
#endif // !defined(EA_315ED3C2_7FF3_40b6_BE9E_BA6558E289F0__INCLUDED_)
