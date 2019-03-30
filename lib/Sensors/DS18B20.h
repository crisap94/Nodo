///////////////////////////////////////////////////////////
//  DS18B20.h
//  Implementation of the Class DS18B20
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_)
#define EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_

#include "OneWire.h"
#include "Sensor.h"

class DS18B20 : public Sensor, public OneWire {
private:
  static DS18B20 *m_ds18b20;

  DS18B20();
  virtual ~DS18B20();

public:
  static DS18B20 *getInstance() {
    if (m_ds18b20 == NULL) {
      m_ds18b20 = new DS18B20();
    }
    return m_ds18b20;
  }
  void begin();
  float getValue();
};
#endif // !defined(EA_2CE8C70C_CC43_4bab_A992_A12AA34F908F__INCLUDED_)
