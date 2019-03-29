///////////////////////////////////////////////////////////
//  PowerSupplyManager.h
//  Implementation of the Class PowerSupplyManager
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_)
#define EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_

#include "Battery.h"
#include "PCF8574.h"
#include "PCF8591.h"
#include "RT9013.h"
#include "SolarPanel.h"
#include "Sensor.h"

class PowerSupplyManager : public Sensor
{

public:
	PowerSupplyManager();
	virtual ~PowerSupplyManager();
	Battery *m_Battery;
	RT9013 *m_RT9013;
	SolarPanel *m_SolarPanel;
	PowerSupplyManager *m_PowerSupplyManager;

	Sensor getInstance();

private:
	Battery Battery;
	PCF8574 pcf8574;
	PCF8591 pcf8591;
	RT9013 RT9013;
	SolarPanel solarPanel;

};
#endif // !defined(EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_)
