///////////////////////////////////////////////////////////
//  PCF8574.h
//  Implementation of the Class PCF8574
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_)
#define EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_

#include "Expander.h"
#include "I2C.h"

class PCF8574 : public I2C, public Expander {
private:
  int address;
  int scl;
  int sda;
  PCF8574();
  virtual ~PCF8574();
  static PCF8574 *m_pcf8574;

public:
  enum PIN {
    /**
    * @brief
    * *Pins from PCF8574
    * ? Available pins from 4 to 7
    */
    TP4056_ENABLE = 0,
    TP4056_STDBY = 1,
    TP4056_CHRG_STATUS = 2,
    RT9013_ENABLE = 3
  };

  static PCF8574 *getInstance() {
    if (m_pcf8574) {
      m_pcf8574 = new PCF8574();
    }

    return m_pcf8574;
  }

  inline void begin();
  boolean getValue(PIN _pin);
  void setValue(PCF8574::PIN _pin, boolean value);
};
#endif // !defined(EA_646D9DC1_B5F4_44ce_BA0A_4F57FCAE4B1A__INCLUDED_)
