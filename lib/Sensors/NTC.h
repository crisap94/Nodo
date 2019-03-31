///////////////////////////////////////////////////////////
//  NTC.h
//  Implementation of the Class NTC
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
#define EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_

#include "Analog.h"
#include "Sensor.h"
#include "pcf8591.h"


class NTC : public Analog, public Sensor {
private:
  static NTC *m_ntc;

  PCF8591 *m_pcf8591;

  int pinConnection;
  int samplingInterval;

  NTC();
  virtual ~NTC();

public:
  static NTC *getInstance() {
    if (m_ntc == NULL) {
      m_ntc = new NTC();
    }
    return m_ntc;
  }
  float getValue();
};
#endif // !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
