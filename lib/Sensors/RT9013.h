///////////////////////////////////////////////////////////
//  RT9013.h
//  Implementation of the Class RT9013
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_)
#define EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_

#include "Digital.h"
#include "PCF8574.h"

class RT9013 : public Digital {
private:
  static RT9013 *m_rt9013;
  PCF8574 *m_pcf8574;

  int pinConnection;
  RT9013();
  virtual ~RT9013();

public:
  enum TP4056_STATUS { ENABLED, DISABLED };
  static RT9013 *getInstance() {
    if (m_rt9013 == NULL) {
      m_rt9013 = new RT9013();
    }
    return m_rt9013;
  }

  void setStatus(RT9013::TP4056_STATUS status);
};
#endif // !defined(EA_8CCEC36F_C3C6_4e24_8C82_5A5D40FBB2E7__INCLUDED_)
