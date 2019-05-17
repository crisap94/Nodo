
#include "ConectionManager.h"


ConectionManager::ConectionManager() {

  mesh = new painlessMesh();

  userScheduler = new Scheduler();

  m_dataManager = new DataManager();

  gatewayId = 0;

  sendJSON = new Task(TASK_SECOND * 5, TASK_FOREVER, [this]() {
    Serial.printf("SLAVE -> Executing Test Task Gateway ID: %u",
                  gatewayId);
    if (gatewayId != 0) {
      const size_t capacity = JSON_OBJECT_SIZE(2);
      DynamicJsonDocument doc(capacity);

      doc["test"] = true;

      String str;
      serializeJson(doc, str);
      Serial.println("SLAVE -> Sending test Packet");
      str = this->m_dataManager->getPayload();
      mesh->sendSingle(gatewayId, str);
    }

  });

}

ConectionManager::~ConectionManager() {
  userScheduler->disableAll();
  mesh->stop();
}

void ConectionManager::begin() {


  mesh->setDebugMsgTypes(ERROR | MSG_TYPES | REMOTE | DEBUG | MESH_STATUS |
                         CONNECTION | COMMUNICATION);

  mesh->init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, MESH_CHANNEL);

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
          Serial.printf("SLAVE -> ID Bridge Gateway Updated!\n");
        }
      }
    }
  });

  userScheduler->addTask(*sendJSON);

  sendJSON->enable();
}

void ConectionManager::loop() {
  mesh->update();
  userScheduler->execute();
}
