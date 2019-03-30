#include <Arduino.h>

#include "DataManager.h"
#include "BME680.h"
#include "CapacitiveSoilMoisture.h"
#include "DS18B20.h"
#include "DS3231.h"
#include "VEML6030.h"
#include "VEML6075.h"
#include "PowerSupplyManager.h"


BME680 *m_BME680;
CapacitiveSoilMoisture *m_CapacitiveSoilMoisture;
DS18B20 *m_ds18b20;
DS3231 *m_ds3231;
VEML6030 *m_veml6030;
VEML6075 *m_veml6075;

PowerSupplyManager *m_powerSupplyManager;

void setup() {
  // put your setup code here, to run once:
  m_BME680 = BME680::getInstance();
  m_CapacitiveSoilMoisture = CapacitiveSoilMoisture::getInstance();
  m_ds18b20 = DS18B20::getInstance();
  m_ds3231 = DS3231::getInstance();
  m_veml6030 = VEML6030::getInstance();
  m_veml6075 = VEML6075::getInstance();
  m_powerSupplyManager = new PowerSupplyManager();
}
  
void loop() {
  // put your main code here, to run repeatedly:
}