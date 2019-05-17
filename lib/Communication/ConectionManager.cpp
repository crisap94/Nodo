
#include "ConectionManager.h"


ConectionManager::ConectionManager() {}

ConectionManager::~ConectionManager() {
  userScheduler->disableAll();
  mesh->stop();
}

void ConectionManager::begin() {

  mesh = new painlessMesh();

  userScheduler = new Scheduler();

  gatewayId = 0;

  requestBridgeId = new Task(TASK_SECOND * 5, TASK_FOREVER, [this]() {

    if (gatewayId == 0) { // If we don't know the logServer yet
      const size_t capacity = JSON_OBJECT_SIZE(2);
      DynamicJsonDocument doc(capacity);

      doc["nodeId"] = mesh->getNodeId();
      doc["requestGatewayId"] = true;

      String str;
      serializeJson(doc, str);
      mesh->sendBroadcast(str);
    }
  });

  test = new Task(TASK_SECOND * 2, TASK_FOREVER, [this]() {
    if (gatewayId != 0) {
      const size_t capacity = JSON_OBJECT_SIZE(2);
      DynamicJsonDocument doc(capacity);

      doc["test"] = true;

      String str;
      serializeJson(doc, str);
      mesh->sendSingle(gatewayId,str);
    }

  });


  mesh->setDebugMsgTypes(ERROR | MSG_TYPES | REMOTE | DEBUG 
                          | MESH_STATUS | CONNECTION );

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
          Serial.printf("ID Bridge Gateway Updated!\n");
        }
      }
      Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
    }
  });

  userScheduler->addTask(*requestBridgeId);
  userScheduler->addTask(*test);
}

void ConectionManager::loop() {
  mesh->update();
  userScheduler->execute();
}
