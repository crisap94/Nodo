///////////////////////////////////////////////////////////
//  CapacitiveSoilMoisture.h
//  Implementation of the Class CapacitiveSoilMoisture
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_)
#define EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_

#include "Analog.h"
#include "PCF8591.h"
#include "Sensor.h"


class CapacitiveSoilMoisture : public Sensor, public Analog {
private:

  static CapacitiveSoilMoisture *m_CapacitiveSoilMoisture;

  PCF8591 *m_pcf8591;

  int pinConnection;
  
  CapacitiveSoilMoisture();
  virtual ~CapacitiveSoilMoisture();

public:
  static CapacitiveSoilMoisture *getInstance(){
	  if(m_CapacitiveSoilMoisture == NULL){
		  m_CapacitiveSoilMoisture = new CapacitiveSoilMoisture();
	  }
    return m_CapacitiveSoilMoisture;
  }

  float getValue();
};
#endif // !defined(EA_3D066AC5_BB3A_49ce_8741_146E2057FE76__INCLUDED_)
