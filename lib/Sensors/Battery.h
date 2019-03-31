///////////////////////////////////////////////////////////
//  Battery.h
//  Implementation of the Class Battery
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_)
#define EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_

#include "Analog.h"
#include "NTC.h"
#include "PCF8591.h"
#include "TP4056.h"

class Battery : public Analog {
private:
  static Battery *m_battery;

  PCF8591 *m_pcf8591;
  
  int pinConnection;
  int samplingInterval;

  TP4056 *m_tp4056;
  NTC *m_ntc;

  Battery();
  virtual ~Battery();

public:
  static Battery *getInstance() {
    if (m_battery == NULL) {
      m_battery = new Battery();
    }
    return m_battery;
  }
  float getTemp();
  float getVoltaje();
  boolean getStatus();
};
#endif // !defined(EA_68E68837_62F6_4f14_97F4_C07D172CDB0E__INCLUDED_)
