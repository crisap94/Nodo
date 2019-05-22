///////////////////////////////////////////////////////////
//  SensorManager.h
//  Implementation of the Interface SensorManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_)
#define EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_



#include "Sensor.h"

class SensorManager {

public:
  SensorManager() {}

  virtual ~SensorManager() {}

  virtual float getData() { return 0; };
};
#endif // !defined(EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_)
