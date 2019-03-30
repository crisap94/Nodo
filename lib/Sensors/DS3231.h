///////////////////////////////////////////////////////////
//  DS3231.h
//  Implementation of the Class DS3231
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_)
#define EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_

#include "I2C.h"
#include "Sensor.h"

class DS3231 : public Sensor, public I2C {
private:
  static DS3231 *m_ds3231;

  DS3231();
  virtual ~DS3231();

public:
  static DS3231 *getInstance() {
    if (m_ds3231 == NULL) {
      m_ds3231 = new DS3231();
    }
    return m_ds3231;
  }

  void begin();
  long getValue();
};
#endif // !defined(EA_13654DAA_29C3_4fb2_A884_C58B464B277D__INCLUDED_)
