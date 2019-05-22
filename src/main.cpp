#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION

#include <TaskScheduler.h>

#include <Scheduller.h>

#include <ESP8266WiFi.h>

#include <ConfigManager.h>

#include <DataManager.h>

#include <FS.h>

void tNotConfigured();
void tConfigured();
void tVerifyConfig();

Scheduler scheduller;

uint8_t configFlag;

ConfigManager *m_configManager;
DataManager *m_dataManager;

Task *tConfigManager;
Task *tDataManager;

Task *tConfig =
    new Task(TASK_SECOND, TASK_FOREVER, tVerifyConfig, &scheduller, true);

void setup() {
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  Serial.begin(115200);
  Serial.println(F("\n\nCONFIG MANAGER TEST"));
  Serial.println(F("===================="));
  Serial.println();
  Serial.printf("D5 %i D6 %i D7 %i\n\n", digitalRead(D5), digitalRead(D6),
                digitalRead(D7));
  if (!digitalRead(D5) || !digitalRead(D6) || !digitalRead(D7)) {
    SPIFFS.format();
  }
  configFlag = false;

  m_configManager = new ConfigManager();
  m_dataManager = new DataManager();

  tConfigManager = m_configManager->tConnect;
  tDataManager = m_dataManager->tMain;

  m_configManager->isConfig();

  // Serial.printf("\nConfig status %s\n", config ? "true" : "false");

  tConfig->waitFor(tConfigManager->getInternalStatusRequest(),TASK_SECOND,TASK_FOREVER);
  // tConfig->enable();
  // tDataManager->waitFor(tConfigManager->getInternalStatusRequest());
  // tConfig->waitFor(tConfigManager->getInternalStatusRequest());
}

void loop() {
  scheduller.execute(); // Only Scheduler should be executed in the loop
  if (m_dataManager->isReady()) {
    String paylaod = m_dataManager->getPayload();
    Serial.println(paylaod);
  }
}

void tNotConfigured() {
  Serial.println("Nodo No Configurado");
  if (configFlag) {
    tConfig->setIterations(TASK_ONCE);
    tConfig->setCallback(m_dataManager->mainFunction);
  }
  // tConfig->disable();
};

void tConfigured() {
  Serial.println("Nodo Configurado");
  // tDataManager->enable();
  tConfig->setIterations(TASK_ONCE);
  tConfig->setCallback(m_dataManager->mainFunction);
};

void tVerifyConfig() {
  Serial.println("Verificando Configuracion Inicial");
  if (configFlag == true) {
    tConfig->setCallback(tConfigured);
  } else if (configFlag == false) {
    tConfig->setCallback(tNotConfigured);
  }
};
