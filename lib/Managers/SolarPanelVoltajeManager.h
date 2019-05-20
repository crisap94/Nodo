///////////////////////////////////////////////////////////
//  SolarPanelVoltajeManager.h
//  Implementation of the Class SolarPanelVoltajeManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_)
#define EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_

#include "PowerSupplyManager.h"
#include "SensorManager.h"

class SolarPanelVoltajeManager : public SensorManager {
private:
  float getData() {
    PowerSupplyManager *ps = new PowerSupplyManager();
    float voltaje = ps->m_solarPanel->getVoltaje();
    delete ps;
    return voltaje;
  }

public:
  SolarPanelVoltajeManager(){};
  virtual ~SolarPanelVoltajeManager(){};

};
#endif // !defined(EA_657FA90A_7FCB_4a34_9758_59AECF8ADE25__INCLUDED_)
