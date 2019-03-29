///////////////////////////////////////////////////////////
//  VEML6075.h
//  Implementation of the Class VEML6075
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_9379FF0E_1B64_4869_B859_4ADF835D3B39__INCLUDED_)
#define EA_9379FF0E_1B64_4869_B859_4ADF835D3B39__INCLUDED_

#include "Sensor.h"
#include "I2C.h"

class VEML6075 : public Sensor, public I2C
{

public:
	VEML6075();
	virtual ~VEML6075();
	VEML6075 *m_VEML6075;

	void begin();
	void getData();
	Sensor getInstance();

};
#endif // !defined(EA_9379FF0E_1B64_4869_B859_4ADF835D3B39__INCLUDED_)
