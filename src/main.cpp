#include <ESP8266WiFi.h>

#include <Wire.h>

//#include "DataManager.h"

#include <BME680.h>
#include <Battery.h>
#include <CapacitiveSoilMoisture.h>
#include <DS3231.h>
#include <SolarPanel.h>
#include <VEML6075.h>

// DataManager *m_dataManager;

Battery *m_batt;
BME680 *m_bme;
VEML6075 *m_veml;
DS3231 *m_ds32;
SolarPanel *m_sol;
CapacitiveSoilMoisture *m_soil;

#define SCL 2
#define SDA 0

void setup() {
  Wire.begin(SDA, SCL);
  Serial.begin(115200);

  delay(2000);

  m_batt = Battery::getInstance();
  m_bme = BME680::getInstance();
  m_ds32 = DS3231::getInstance();
  m_veml = VEML6075::getInstance();
  m_sol = SolarPanel::getInstance();
  m_soil = CapacitiveSoilMoisture::getInstance();

  // m_dataManager = new DataManager();
}

void loop() {

  Serial.printf("BattT: %2.1f BattV: %1.1f PanelV: %1.1f Hum: %2.1f "
                "Temp: %2.1f Press: %4.1f VOC: %3.1f EPOCH: %lld UV: %1.1f SoilH: %3.0f\n",
                m_batt->getTemp(), m_batt->getVoltaje(), m_sol->getVoltaje(),
                m_bme->getHumidity(), m_bme->getTemperature(),
                m_bme->getPressure(), m_bme->getVOC(), m_ds32->getValue(),
                m_veml->getValue(),m_soil->getValue());

  // m_dataManager->loop();
  // if (m_dataManager->isReady()) {
  //   Serial.println(m_dataManager->getPayload());
  // }

  // Serial.println(m_dataManager->getJSON());
}