///////////////////////////////////////////////////////////
//  PowerSupplyManager.h
//  Implementation of the Class PowerSupplyManager
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_)
#define EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_

#include "Battery.h"
#include "RT9013.h"
#include "Sensor.h"
#include "SolarPanel.h"

class PowerSupplyManager : public Sensor {
private:
  Battery *m_battery;
  RT9013 *m_rt9013;
  SolarPanel *m_solarPanel;

public:

  PowerSupplyManager() {
    this->m_battery = Battery::getInstance();
    this->m_rt9013 = RT9013::getInstance();
    this->m_solarPanel = SolarPanel::getInstance();
  }
  virtual ~PowerSupplyManager() {}

};
#endif // !defined(EA_523D047F_31C6_48c8_A90D_8F964071951E__INCLUDED_)
