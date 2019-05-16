#include <ESP8266WiFi.h>

#include <ConectionManager.h>

ConectionManager *m_conectionManager = new ConectionManager();

void setup() {
  Serial.begin(115200);
  m_conectionManager->begin();
}

void loop() {
  m_conectionManager->loop();
}

