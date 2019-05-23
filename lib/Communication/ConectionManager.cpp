
#include "ConectionManager.h"

ConectionManager::ConectionManager() {

  Serial.println(F("\n\nCONECTION MANAGER -> Creating MESH Object"));
  mesh = new painlessMesh();

  gatewayId = 0;

  Serial.println(F("CONECTION MANAGER -> Creating MESH task"));

  tMesh = new Task(TASK_SECOND, TASK_ONCE, initMesh, &scheduller);



  Serial.println(F("CONECTION MANAGER -> Creating message Task"));
  tSendMessage =
      new Task(TASK_SECOND * 5, TASK_FOREVER, sendMessage, &scheduller);

  sendMessage = [this]() {
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

  initMesh = [this]() {
    
    Serial.println(F("CONECTION MANAGER -> Init MESH "));
    mesh->init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA,
               MESH_CHANNEL);

    tSendMessage->enable();

    tMesh->disable();
  };
}

ConectionManager::~ConectionManager() { mesh->stop(); }

void ConectionManager::loop() { mesh->update(); }
