///////////////////////////////////////////////////////////
//  NTC.h
//  Implementation of the Class NTC
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
#define EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_

#include "Sensor.h"
#include "PCF8591.h"

#define R_AT_25 10000
#define BCOEF 3950
#define R1 10000
#define TEMPERATURENOMINAL 25
#define KELVIN_AT_25 298.15
#define Vin 3.3

class NTC : public Sensor {
private:
  static NTC *m_ntc;

  PCF8591 *m_pcf8591;

  /**
   * Analog pin
   */
  uint16_t analogPin;


  NTC();

  virtual ~NTC();
  

public:
  static NTC *getInstance() {
    if (m_ntc == NULL) {
      m_ntc = new NTC();
    }
    return m_ntc;
  }

  double getValue();

};
#endif // !defined(EA_CE9233F3_0BB0_419e_A745_11B236F4F9B4__INCLUDED_)
