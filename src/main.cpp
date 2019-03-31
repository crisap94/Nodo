#include "ESP8266WiFi.h"

#include "DataManager.h"


/* #include "BME680.h"
#include "CapacitiveSoilMoisture.h"
#include "DS18B20.h"
#include "DS3231.h"
#include "VEML6030.h"
#include "VEML6075.h"
#include "PowerSupplyManager.h" */

/* #include "AmbientTemperatureManager.h"
#include "AmbientHumidityManager.h"
#include "AtmosphericPressureManager.h"
#include "BatteryStatusManager.h"
#include "BatteryTemperatureManager.h"
#include "BatteryVoltajeManager.h"
#include "BrightnessManager.h"
#include "RelativeHumidityManager.h"
#include "RTCManager.h"
#include "SensorManager.h"
#include "SoilMoistureManager.h"
#include "SoilTempManager.h"
#include "SolarPanelVoltajeManager.h"
#include "UltraVioletIndexManager.h"
#include "VolatileOrganicCompoundsManager.h" */

/* BME680 *m_bme680;
CapacitiveSoilMoisture *m_CapacitiveSoilMoisture;
DS18B20 *m_ds18b20;
DS3231 *m_ds3231;
VEML6030 *m_veml6030;
VEML6075 *m_veml6075;
PowerSupplyManager *m_powerSupplyManager; */

/* AmbientTemperatureManager *m_AmbientTemperatureManager;
AmbientHumidityManager *m_AmbientHumidityManager;
AtmosphericPressureManager *m_AtmosphericPressureManager;
BatteryStatusManager *m_BatteryStatusManager;
BatteryTemperatureManager *m_BatteryTemperatureManager;
BatteryVoltajeManager *m_BatteryVoltajeManager;
BrightnessManager *m_BrightnessManager;
RelativeHumidityManager *m_RelativeHumidityManager;
RTCManager *m_RTCManager;
SoilMoistureManager *m_SoilMoistureManager;
SoilTempManager *m_SoilTempManager;
SolarPanelVoltajeManager *m_SolarPanelVoltajeManager;
UltraVioletIndexManager *m_UltraVioletIndexManager;
VolatileOrganicCompoundsManager *m_VolatileOrganicCompoundsManager; */



DataManager *m_dataManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  // put your setup code here, to run once:

/*   m_bme680 = BME680::getInstance();
  m_CapacitiveSoilMoisture = CapacitiveSoilMoisture::getInstance();
  m_ds18b20 = DS18B20::getInstance();
  m_ds3231 = DS3231::getInstance();
  m_veml6030 = VEML6030::getInstance();
  m_veml6075 = VEML6075::getInstance();
  m_powerSupplyManager = new PowerSupplyManager(); */

  m_dataManager = new DataManager();


}

void loop()
{
/*   m_AmbientTemperatureManager = new AmbientTemperatureManager();
  m_AmbientHumidityManager = new AmbientHumidityManager();
  m_AtmosphericPressureManager = new AtmosphericPressureManager();
  m_BatteryStatusManager = new BatteryStatusManager();
  m_BatteryTemperatureManager = new BatteryTemperatureManager();
  m_BatteryVoltajeManager = new BatteryVoltajeManager();
  m_BrightnessManager = new BrightnessManager();
  m_RelativeHumidityManager = new RelativeHumidityManager();
  m_RTCManager = new RTCManager();
  m_SoilMoistureManager = new SoilMoistureManager();
  m_SoilTempManager = new SoilTempManager();
  m_SolarPanelVoltajeManager = new SolarPanelVoltajeManager();
  m_UltraVioletIndexManager = new UltraVioletIndexManager();
  m_VolatileOrganicCompoundsManager = new VolatileOrganicCompoundsManager(); */
  // put your main code here, to run repeatedly:
  delay(10);
  m_dataManager->getPayload();
/*   Serial.println("Free RAM:" + String(ESP.getFreeHeap()) + "\t");
  Serial.print("TEMP:" + String(m_AmbientTemperatureManager->getCleanedData()) + "\t");
  Serial.print("HUM:" + String(m_AmbientHumidityManager->getCleanedData()) + "\t");
  Serial.print("PRESS:" + String(m_AtmosphericPressureManager->getCleanedData()) + "\t");
  Serial.print("SOILH:" + String(m_SoilMoistureManager->getCleanedData()) + "\t");
  Serial.print("SOILT:" + String(m_SoilTempManager->getCleanedData()) + "\t");
  Serial.print("EPOCH:" + String(m_RTCManager->getCleanedData()) + "\t");
  Serial.print("BRIGH:" + String(m_BrightnessManager->getCleanedData()) + "\t");
  Serial.print("UV:" + String(m_UltraVioletIndexManager->getCleanedData()) + "\t");
  Serial.print("BAT_T:" + String(m_BatteryTemperatureManager->getCleanedData()) + "\t");
  Serial.print("BAT_S:" + String(m_BatteryStatusManager->getCleanedData()) + "\t");
  Serial.print("BAT_V:" + String(m_BatteryVoltajeManager->getCleanedData()) + "\t");
  Serial.print("SOLAR:" + String(m_SolarPanelVoltajeManager->getCleanedData())); */

/*   delete m_AmbientTemperatureManager;
  delete m_AmbientHumidityManager;
  delete m_AtmosphericPressureManager;
  delete m_BatteryStatusManager;
  delete m_BatteryTemperatureManager;
  delete m_BatteryVoltajeManager;
  delete m_BrightnessManager;
  delete m_RelativeHumidityManager;
  delete m_RTCManager;
  delete m_SoilMoistureManager;
  delete m_SoilTempManager;
  delete m_SolarPanelVoltajeManager;
  delete m_UltraVioletIndexManager;
  delete m_VolatileOrganicCompoundsManager; */

  delay(10);
}