#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION

#include <TaskScheduler.h>

#include <Scheduller.h>

#include <ESP8266WiFi.h>

#include <ConectionManager.h>

#include <ConfigManager.h>

#include <DataManager.h>

#include <FS.h>

void tNotConfigured();
void tConfigured();
void tVerifyConfig();

Scheduler scheduller;

uint8_t configFlag;

ConectionManager *m_conectionManager;
ConfigManager *m_configManager;
DataManager *m_dataManager;

Task *tConectionManager;
Task *tConfigManager;
Task *tDataManager;

Task *tSensors =
    new Task(TASK_SECOND, TASK_FOREVER, tVerifyConfig, &scheduller);

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
  tConectionManager = m_conectionManager->tMesh;

  m_configManager->isConfig();

  // Serial.printf("\nConfig status %s\n", config ? "true" : "false");
  tConectionManager->waitFor(tConfigManager->getInternalStatusRequest(),
                             TASK_ONCE, TASK_FOREVER);
  tSensors->waitFor(tConectionManager->getInternalStatusRequest(), TASK_SECOND,
                    TASK_FOREVER);
  // tSensors->enable();
  // tDataManager->waitFor(tConfigManager->getInternalStatusRequest());
  // tSensors->waitFor(tConfigManager->getInternalStatusRequest());
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
    tSensors->setIterations(TASK_ONCE);
    tSensors->setCallback(m_dataManager->mainFunction);
  }
  // tSensors->disable();
};

void tConfigured() {
  Serial.println("Nodo Configurado");
  // tDataManager->enable();
  tSensors->setIterations(TASK_ONCE);
  tSensors->setCallback(m_dataManager->mainFunction);
};

void tVerifyConfig() {
  Serial.println("Verificando Configuracion Inicial");
  if (configFlag == true) {
    tSensors->setCallback(tConfigured);
  } else if (configFlag == false) {
    tSensors->setCallback(tNotConfigured);
  }
};
