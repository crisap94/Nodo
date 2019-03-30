///////////////////////////////////////////////////////////
//  SolarPanel.h
//  Implementation of the Class SolarPanel
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_)
#define EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_

#include "Analog.h"
#include "pcf8591.h"


class SolarPanel : public Analog {
private:
  static SolarPanel *m_solarPanel;
  PCF8591 *m_pcf8591;

  int pinConnection;
  int samplingInterval;

  SolarPanel();
  virtual ~SolarPanel();

public:
  static SolarPanel *getInstance() {
    if (m_solarPanel == NULL) {
      m_solarPanel = new SolarPanel();
    }
    return m_solarPanel;
  }

  float getVoltaje();
};
#endif // !defined(EA_9B61CC94_5CE1_402b_9A8A_AF70A2F59093__INCLUDED_)
