#include <Arduino.h>

#include "DataManager.h"
#include "BME680.h"

BME680 *m_BME680;
void setup() {
  // put your setup code here, to run once:
  m_BME680 = BME680::getInstance();
}

void loop() {
  // put your main code here, to run repeatedly:
}