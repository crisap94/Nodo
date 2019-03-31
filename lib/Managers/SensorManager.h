///////////////////////////////////////////////////////////
//  SensorManager.h
//  Implementation of the Interface SensorManager
//  Created on:      28-Mar-2019 4:29:37 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_)
#define EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_

#include "DataCleaner.h"
#include "ESP8266WiFi.h"
#include "Sensor.h"

class SensorManager {

public:
  SensorManager() {}

  virtual ~SensorManager() {}
  // std::function<void (const long&)> _callBackFunction
  // void (*_callBackFunction)(long data)

  virtual long getCleanedData(function<void(const long &)> _callBackFunction) {
    DataCleaner<long> *sensor = new DataCleaner<long>;
    sensor->begin(SMOOTHED_EXPONENTIAL, 10);
    for (int i = 0; i < 10; i++) {
      sensor->add(getData());
      yield();
    }
    long value = sensor->get();
    delete sensor;
    _callBackFunction(value);
    return value;
  }

  virtual float getData() { return 0; };
};
#endif // !defined(EA_B3F3D724_985C_4bb8_B895_BA6B571D95BD__INCLUDED_)