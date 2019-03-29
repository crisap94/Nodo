///////////////////////////////////////////////////////////
//  PCF8591.h
//  Implementation of the Class PCF8591
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
#define EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_

#include "I2C.h"
#include "Expander.h"

class PCF8591 : public I2C, public Expander
{

public:
	PCF8591();
	virtual ~PCF8591();
	PCF8591 *m_PCF8591;

	inline void begin(){

	}
	void getData();

};
#endif // !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
