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
  private:
	int address;
	int scl;
	int sda;
	static VEML6075 *m_veml6075;

	VEML6075();
	virtual ~VEML6075();

  public:
	static VEML6075 *getInstance()
	{
		if (m_veml6075 == NULL)
		{
			m_veml6075 = new VEML6075();
		}
		return m_veml6075;
	}
	void begin();
	float getValue();
};
#endif // !defined(EA_9379FF0E_1B64_4869_B859_4ADF835D3B39__INCLUDED_)
