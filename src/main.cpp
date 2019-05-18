#include <ESP8266WiFi.h>

#include <Wire.h>

#include "DataManager.h"

DataManager *m_dataManager;

#define SCL 2
#define SDA 0

void setup() {
  Wire.begin(SDA, SCL);
  Serial.begin(115200);

  delay(2000);

  m_dataManager = new DataManager();
}

void loop() {
  m_dataManager->loop();

  if (m_dataManager->isReady()) {
    Serial.println(m_dataManager->getPayload());
  }

  // Serial.println(m_dataManager->getJSON());
  
}