#include <ESP8266WiFi.h>

#include <Wire.h>

#include "DataManager.h"
Scheduler *taskScheduller;
DataManager *m_dataManager;
ConfigManager *m_configManager;

#define SCL 2
#define SDA 0

void setup() {
  Wire.begin(SDA, SCL);
  Wire.setClock(3400000);
  Serial.begin(115200);
  taskScheduller = new Scheduler();
  delay(2000);

  m_dataManager = new DataManager(taskScheduller);
}

void loop() {
  m_dataManager->loop();

  if (m_dataManager->isReady()) {
    Serial.println(m_dataManager->getPayload());
  }

  // Serial.println(m_dataManager->getJSON());
  
}