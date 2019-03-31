///////////////////////////////////////////////////////////
//  TP4056.h
//  Implementation of the Class TP4056
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_)
#define EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_

#include "Digital.h"
#include "PCF8574.h"

enum Status {
  CHARGING,
  STAND_BY
};

class TP4056 : public Digital {
private:
  static TP4056 *m_tp4056;
  PCF8574 *m_pcf8574;
  TP4056();
  virtual ~TP4056();
  int pinChrg;
  int pinStby;
  int pinEnable;

public:
  static TP4056 *getInstance() {
    if (m_tp4056 == NULL) {
      m_tp4056 = new TP4056();
    }
    return m_tp4056;
  }

  boolean getStatus();
  void enable();
};
#endif // !defined(EA_E627994B_0A23_4553_A41E_96984CEF63D0__INCLUDED_)
