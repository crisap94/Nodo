///////////////////////////////////////////////////////////
//  PCF8591.h
//  Implementation of the Class pcf8591
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
#define EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_

#include "Expander.h"
#include "I2C.h"

class PCF8591 : public I2C, public Expander {
private:
  int address;
  int scl;
  int sda;
  PCF8591();
  virtual ~PCF8591();
  static PCF8591 *m_pcf8591;

public:
  enum PIN {
    /**
     * @brief
     * * Pins from PCF8591
     *
     */
    BATT_TEMPERATURE_VOLTAJE = 0,
    BATT_VOLTAJE = 1,
    SOIL_HUMIDITY_VOLTAJE = 2,
    PANEL_VOLTAJE = 3,
  };
  static PCF8591 *getInstance() {
    if (m_pcf8591) {
      m_pcf8591 = new PCF8591();
    }

    return m_pcf8591;
  }
  void begin();
  float getValue(PCF8591::PIN _pin);
};
#endif // !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
