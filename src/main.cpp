#include <Scheduller.hpp>

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION
#define _TASK_PRIORITY

#include <TaskScheduler.h>

#include <ConfigManager.h>

#include <painlessMesh.h>

#include <DataManager.h>

#include <FS.h>

#define MESH_PREFIX "smava"
#define MESH_PASSWORD "smava1234"
#define MESH_PORT 5555
#define MESH_CHANNEL 4

void initMesh();
void sendMessage();

void cNotConfigured();
void cConfigured();
void tVerifyConfig();

Scheduler scheduller;

uint8_t configFlag = false;

painlessMesh *mesh = new painlessMesh();
ConfigManager *m_configManager;
DataManager *m_dataManager;

Task *tConfigManager;

Task *tConectionManager =
    new Task(TASK_SECOND, TASK_ONCE, initMesh, &scheduller);

Task *tDataManager;

Task *tSensors =
    new Task(TASK_SECOND, TASK_FOREVER, tVerifyConfig, &scheduller);

Task *tSendMessage =
    new Task(TASK_SECOND * 5, TASK_FOREVER, sendMessage, &scheduller);

uint32_t gatewayId = 0;

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

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("MAIN -> Disconecting from previus connection"));
    WiFi.disconnect();
  }

  m_configManager = new ConfigManager();
  m_dataManager = new DataManager();

  tConfigManager = m_configManager->tConnect;
  tDataManager = m_dataManager->tMain;

  tConfigManager->setCallback(m_configManager->checkInitialConfig);
  tConfigManager->enable();

  tConectionManager->waitFor(tConfigManager->getInternalStatusRequest());


  tSendMessage->waitFor(tConectionManager->getInternalStatusRequest(),
                       TASK_SECOND * 5, TASK_FOREVER);

  // tMainConfig = m_configManager->tConfig;

  // tMainConfig->enable();
  // tMainConfig->setCallback(m_configManager->checkInitialConfig);
  // tMainConfig->enable();
  // tConfigManager->enable();

  // Serial.printf("\nConfig status %s\n", config ? "true" : "false");

  // tSensors->waitFor(tConectionManager->getInternalStatusRequest(),
  // TASK_SECOND,
  //                  TASK_FOREVER);
  // tSensors->enable();
  tDataManager->setCallback(m_dataManager->mainFunction);
  tDataManager->waitFor(tConectionManager->getInternalStatusRequest());

  // tSensors->waitFor(tConfigManager->getInternalStatusRequest());
  scheduller.startNow();
}

void loop() {
  scheduller.execute(); // Only Scheduler should be executed in the loop
  mesh->update();
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
}

void sendMessage() {
  if (gatewayId != 0) {
    Serial.println(F("CONECTION MANAGER -> Gateway Connected"));
    const size_t capacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);

    doc["test"] = true;

    String str;
    serializeJson(doc, str);
    Serial.println("CONECTION MANAGER -> Sending test Packet");
    // str = this->m_dataManager->getPayload();
    mesh->sendSingle(gatewayId, str);
    tSendMessage->disable();

  } else {
    Serial.println(F("CONECTION MANAGER -> Gateway not visible yet"));
  }
};

void initMesh() {
  Serial.println(F("CONECTION MANAGER -> Setting up DEBUG messages"));
  mesh->setDebugMsgTypes(ERROR | STARTUP | MESH_STATUS | CONNECTION | SYNC |
                        S_TIME | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE |
                        APPLICATION | DEBUG);

  Serial.println(F("CONECTION MANAGER -> Setting up on recive callback"));
  mesh->onReceive([](const uint32_t &from, const String &msg) {
    Serial.printf("Message: Received from %u msg=%s\n", from, msg.c_str());

    const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, msg);

    if (doc.containsKey("gateway")) {
      if (gatewayId == 0) {
        if (String("mqtt").equals(doc["gateway"].as<String>())) {
          // check for on: true or false
          gatewayId = doc["nodeId"];
          Serial.printf("CONECTION MANAGER -> ID Bridge Gateway Updated!\n");
        }
      }
    }
  });

  Serial.println(F("CONECTION MANAGER -> Init MESH "));
  mesh->init("WhateverYouLike", "SomethingSneaky",&scheduller ,5555, WIFI_AP_STA, 4);
};
