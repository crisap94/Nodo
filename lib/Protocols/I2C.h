///////////////////////////////////////////////////////////
//  I2C.h
//  Implementation of the Interface I2C
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_44F000DA_001B_4524_93EE_01CD0F97602E__INCLUDED_)
#define EA_44F000DA_001B_4524_93EE_01CD0F97602E__INCLUDED_

#include "Arduino.h"

class I2C {

public:
  I2C() {}

  virtual ~I2C() {}

  inline void begin();

protected:
  int address;
  int scl;
  int sda;
};
#endif // !defined(EA_44F000DA_001B_4524_93EE_01CD0F97602E__INCLUDED_)
