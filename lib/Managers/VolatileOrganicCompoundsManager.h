///////////////////////////////////////////////////////////
//  VolatileOrganicCompoundsManager.h
//  Implementation of the Class VolatileOrganicCompoundsManager
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_DB6E1206_39DD_4472_9043_07339B6F4784__INCLUDED_)
#define EA_DB6E1206_39DD_4472_9043_07339B6F4784__INCLUDED_

#include "BME680.h"
#include "SensorManager.h"


class VolatileOrganicCompoundsManager : public SensorManager {
private:
  float getData() { return BME680::getInstance()->getVOC(); }

public:
  VolatileOrganicCompoundsManager();
  virtual ~VolatileOrganicCompoundsManager();
};
#endif // !defined(EA_DB6E1206_39DD_4472_9043_07339B6F4784__INCLUDED_)
