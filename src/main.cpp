#include "ESP8266WiFi.h"

#include "DataManager.h"

DataManager *m_dataManager;

void setup() {
  Serial.begin(115200);
  delay(2000);

  m_dataManager = new DataManager();
}

void loop() {

  delay(10);
  // Serial.println(m_dataManager->getJSON());
  m_dataManager->getJSON();
  Serial.println("FREE RAM:" + String(ESP.getFreeHeap()));

  delay(10);
}