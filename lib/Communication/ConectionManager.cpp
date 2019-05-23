
#include "ConectionManager.h"

ConectionManager::ConectionManager() {

  Serial.println(F("\n\nCONECTION MANAGER -> Creating MESH Object"));
  mesh = new painlessMesh();

  gatewayId = 0;

  Serial.println(F("CONECTION MANAGER -> Creating MESH task"));

  tMesh = new Task(TASK_SECOND, TASK_ONCE, initMesh, &scheduller);

  mesh->setDebugMsgTypes(ERROR | MSG_TYPES | REMOTE | DEBUG | MESH_STATUS |
                         CONNECTION | COMMUNICATION);

  mesh->onReceive([this](const uint32_t &from, const String &msg) {
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
