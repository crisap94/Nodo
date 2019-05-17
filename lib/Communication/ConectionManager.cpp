
#include "ConectionManager.h"

ConectionManager::ConectionManager()
    : myIP(192, 168, 0, 150), MQTT_BROKER_IP(206, 189, 202, 242) {}

ConectionManager::~ConectionManager() {
  userScheduler->disableAll();
  mqttClient->disconnect();
  mesh->stop();
}

void ConectionManager::begin() {

  wifiClient = new WiFiClient();
  mqttClient = new PubSubClient();
  mqttClient->setServer(MQTT_BROKER_IP, MQTT_PORT);
  mqttClient->setClient(*wifiClient);
  mesh = new painlessMesh();

  GATEWAY_OUTPUT_NODES_TOPIC = "painlessMesh/from/nodes";
  GATEWAY_OUTPUT_TOPIC = "painlessMesh/from/gateway";
  GATEWAY_IN_TOPIC = "painlessMesh/to/#";

  userScheduler = new Scheduler();

  bridgeACK = new Task(TASK_SECOND * 5, TASK_FOREVER, [this]() {
    const size_t capacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);

    doc["gateway"] = "mqtt";
    doc["nodeId"] = mesh->getNodeId();

    String str;
    serializeJson(doc, str);

    mesh->sendBroadcast(str);
  });

  mqttBrokerConnection = new Task(TASK_SECOND * 1, TASK_FOREVER, [this]() {
    if (myIP != getlocalIP()) {
      myIP = getlocalIP();
      Serial.println("My IP is " + myIP.toString());
      if (mqttClient->connect(MQTT_CLIENT, MQTT_USER, MQTT_PASSWORD)) {

        Serial.println("Connected to Broker");
        Serial.printf("MQTT Connection Status: %i \n", mqttClient->state());

        const size_t capacity = JSON_OBJECT_SIZE(2);
        DynamicJsonDocument doc(capacity);

        doc["gateway"] = mesh->getNodeId();
        doc["status"] = true;

        String str;
        serializeJson(doc, str);

        mqttClient->publish(GATEWAY_OUTPUT_TOPIC.c_str(), str.c_str());
        mqttClient->subscribe(GATEWAY_IN_TOPIC.c_str());
      }
    }
  });

  // Broker Ip Address

  mqttClient->setCallback(
      [this](char *topic, uint8_t *payload, unsigned int length) {
        char *cleanPayload = (char *)malloc(length + 1);
        payload[length] = '\0';
        memcpy(cleanPayload, payload, length + 1);
        String msg = String(cleanPayload);
        free(cleanPayload);

        String targetStr = String(topic).substring(16);

        if (targetStr == "gateway") {
          if (msg == "getNodes") {
            mqttClient->publish("painlessMesh/from/gateway",
                                mesh->subConnectionJson().c_str());
          }
        } else if (targetStr == "broadcast") {
          mesh->sendBroadcast(msg);
        } else {
          uint32_t target = strtoul(targetStr.c_str(), NULL, 10);
          if (mesh->isConnected(target)) {
            mesh->sendSingle(target, msg);
          } else {
            const size_t capacity = JSON_OBJECT_SIZE(2);
            DynamicJsonDocument doc(capacity);

            doc["node"] = target;
            doc["status"] = false;

            String str;
            serializeJson(doc, str);

            mqttClient->publish(GATEWAY_OUTPUT_TOPIC.c_str(), str.c_str());
          }
        }
      });

  mesh->setDebugMsgTypes(MSG_TYPES | REMOTE | DEBUG | MESH_STATUS | CONNECTION | COMMUNICATION);

  mesh->init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, MESH_CHANNEL);

  mesh->onReceive([this](const uint32_t &from, const String &msg) {
    Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
    mqttClient->publish(GATEWAY_OUTPUT_NODES_TOPIC.c_str(), msg.c_str());
  });

  mesh->stationManual(STATION_SSID, STATION_PASSWORD);
  mesh->setHostname(HOSTNAME);

  userScheduler->addTask(*bridgeACK);
  userScheduler->addTask(*mqttBrokerConnection);

  bridgeACK->enable();
  mqttBrokerConnection->enable();
}

IPAddress ConectionManager::getlocalIP() {
  return IPAddress(mesh->getStationIP());
}

void ConectionManager::loop() {
  mesh->update();
  mqttClient->loop();
  userScheduler->execute();
}
