///////////////////////////////////////////////////////////
//  RTCManager.h
//  Implementation of the Class RTCManager
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_63376D6A_3BA1_4b40_B100_76A9BC55088F__INCLUDED_)
#define EA_63376D6A_3BA1_4b40_B100_76A9BC55088F__INCLUDED_

#include "SensorManager.h"
#include "DS3231.h"

class RTCManager : public SensorManager {
private:
  float getValue() { return DS3231::getInstance()->getValue(); }

public:
  RTCManager();
  virtual ~RTCManager();

  long getCleanedData() { return getValue(); }
};
#endif // !defined(EA_63376D6A_3BA1_4b40_B100_76A9BC55088F__INCLUDED_)
