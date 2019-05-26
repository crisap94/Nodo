#include <Scheduller.hpp>

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION
#define _TASK_PRIORITY

#include <TaskScheduler.h>

#include <ConectionManager.h>

#include <ConfigManager.h>

#include <DataManager.h>

#include <FS.h>

void cNotConfigured();
void cConfigured();
void tVerifyConfig();

Scheduler scheduller;

uint8_t configFlag = false;

ConectionManager *m_conectionManager;
ConfigManager *m_configManager;
DataManager *m_dataManager;

Task *tMainConfig = new Task(TASK_SECOND, TASK_ONCE, 0, &scheduller);

Task *tConfigManager;

Task *tConectionManager;

Task *tDataManager;

Task *tSensors =
    new Task(TASK_SECOND, TASK_FOREVER, tVerifyConfig, &scheduller);

void setup() {
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  Serial.begin(115200);
  Serial.println(F("GARBAGE!!!!!!!!!!!!!!!!!!!!!!!!"));
  Serial.println(
      F("============================================================"));
  Serial.println(
      F("                         NODO SLAVE                         "));
  Serial.println(
      F("============================================================"));
  Serial.print("\n\n");
  Serial.println(
      F("MAIN -> Checking GPIO's to reset the SPIFF from the SLAVE"));

  Serial.printf("D5 %i D6 %i D7 %i\n\n", digitalRead(D5), digitalRead(D6),
                digitalRead(D7));

  if (!digitalRead(D5) || !digitalRead(D6) || !digitalRead(D7)) {
    Serial.print(F("MAIN -> Formating SPIFF\n\n"));
    SPIFFS.format();
    Serial.print(F("MAIN -> SPIFF Formated\n\n"));
  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println(F("MAIN -> Disconecting from previus connection"));
    WiFi.disconnect();
  }

  m_configManager = new ConfigManager();
  m_conectionManager = new ConectionManager();
  m_dataManager = new DataManager();

  tConfigManager = m_configManager->tConnect;
  tConectionManager = m_conectionManager->tMesh;
  tDataManager = m_dataManager->tMain;

  tConfigManager->setCallback(m_configManager->checkInitialConfig);
  tConfigManager->enable();

  // tMainConfig = m_configManager->tConfig;

  // tMainConfig->enable();
  // tMainConfig->setCallback(m_configManager->checkInitialConfig);
  // tMainConfig->enable();
  // tConfigManager->enable();

  // Serial.printf("\nConfig status %s\n", config ? "true" : "false");
  tConectionManager->setCallback(m_conectionManager->initMesh);
  tConectionManager->waitFor(tConfigManager->getInternalStatusRequest(),
                             TASK_SECOND, TASK_FOREVER);

  //tSensors->waitFor(tConectionManager->getInternalStatusRequest(), TASK_SECOND,
  //                  TASK_FOREVER);
  // tSensors->enable();
  tDataManager->setCallback(m_dataManager->mainFunction);
  tDataManager->waitFor(tConectionManager->getInternalStatusRequest());

  //tSensors->waitFor(tConfigManager->getInternalStatusRequest());
  scheduller.startNow();
}

void loop() {
  scheduller.execute(); // Only Scheduler should be executed in the loop
  m_conectionManager->loop();
  if (m_dataManager->isReady()) {
    String paylaod = m_dataManager->getPayload();
    Serial.println(paylaod);
  }
}

void cNotConfigured() {
  Serial.println("Nodo No Configurado");
  if (configFlag) {
    tSensors->setIterations(TASK_ONCE);
    tSensors->setCallback(m_dataManager->mainFunction);
  }
  // tSensors->disable();
};

void cConfigured() {
  Serial.println("Nodo Configurado");
  // tDataManager->enable();
  tSensors->setIterations(TASK_ONCE);
  tSensors->setCallback(m_dataManager->mainFunction);
};

void tVerifyConfig() {
  Serial.println("Verificando Configuracion Inicial");
  if (configFlag == true) {
    tSensors->setCallback(cConfigured);
  } else if (configFlag == false) {
    tSensors->setCallback(cNotConfigured);
  }
};
