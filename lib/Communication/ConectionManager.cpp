
#include "ConectionManager.h"

ConectionManager::ConectionManager()
    : myIP(192, 168, 0, 150), MQTT_BROKER_IP(206, 189, 202, 242) {

  Serial.println(F("\n\nCONECTION MANAGER -> Creating WiFi Client"));
  wifiClient = new WiFiClient();

  Serial.println(F("CONECTION MANAGER -> Creating Mqtt Client"));
  mqttClient = new PubSubClient();

  Serial.println(F("CONECTION MANAGER -> Configuring Mqtt Client"));

  Serial.print(F("CONECTION MANAGER -> Broker IP:"));
  Serial.println(MQTT_BROKER_IP);

  Serial.print(F("CONECTION MANAGER -> Mqtt Port:"));
  Serial.println(MQTT_PORT);

  mqttClient->setServer(MQTT_BROKER_IP, MQTT_PORT);
  mqttClient->setClient(*wifiClient);

  Serial.print(F("CONECTION MANAGER -> Nodes Output topic: "));
  GATEWAY_OUTPUT_NODES_TOPIC = "5ac012583e194204e0afef6b";
  Serial.println(GATEWAY_OUTPUT_NODES_TOPIC);

  Serial.print(F("CONECTION MANAGER -> Gateway Output topic: "));
  GATEWAY_OUTPUT_TOPIC = "mesh/from/gateway";
  Serial.println(GATEWAY_OUTPUT_TOPIC);

  Serial.print(F("CONECTION MANAGER -> Gateway In topic: "));
  GATEWAY_IN_TOPIC = "mesh/to/#";
  Serial.println(GATEWAY_IN_TOPIC);

  Serial.println(F("CONECTION MANAGER -> Creating MQTT-Bridge Task"));
  bridgeACK = new Task(TASK_SECOND * 5, TASK_FOREVER,
                       [this]() {
                         const size_t capacity = JSON_OBJECT_SIZE(2);
                         DynamicJsonDocument doc(capacity);

                         doc["gateway"] = "mqtt";
                         doc["nodeId"] = mesh->getNodeId();

                         String str;
                         serializeJson(doc, str);

                         mesh->sendBroadcast(str);
                       },
                       &scheduller);

  Serial.println(F("CONECTION MANAGER -> Creating MQTT-Broker Connection Task"));
  mqttBrokerConnection = new Task(
      TASK_SECOND * 1, TASK_FOREVER,
      [this]() {
        if (myIP != getlocalIP()) {
          myIP = getlocalIP();
          Serial.println("My IP is " + myIP.toString());
          if (mqttClient->connect(MQTT_CLIENT, MQTT_USER, MQTT_PASSWORD)) {

            Serial.println("CONNECTION MANAGER -> Connected to Broker");
            Serial.printf("CONNECTION MANAGER -> MQTT Connection Status: %i \n",
                          mqttClient->state());

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
      },
      &scheduller);

  mqttClient->setCallback(
      [this](char *topic, uint8_t *payload, unsigned int length) {
        char *cleanPayload = (char *)malloc(length + 1);
        payload[length] = '\0';
        memcpy(cleanPayload, payload, length + 1);
        String msg = String(cleanPayload);
        free(cleanPayload);

        String targetStr = String(topic).substring(8);

        if (targetStr == "gateway") {
          if (msg == "getNodes") {
            mqttClient->publish("mesh/from/gateway",
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

  Serial.println(F("CONECTION MANAGER -> Creating MESH task"));

  tMesh = new Task(TASK_SECOND, TASK_ONCE, initMesh, &scheduller);

  initMesh = [this]() {

    Serial.println(F("CONECTION MANAGER -> Creating MESH Object"));
    mesh = new painlessMesh();

    Serial.println(F("CONECTION MANAGER -> Setting up Debug Messages"));
    mesh->setDebugMsgTypes(ERROR | MSG_TYPES | REMOTE | DEBUG | MESH_STATUS |
                           CONNECTION);


    Serial.println(F("CONECTION MANAGER -> Init MESH "));
    mesh->init(MESH_PREFIX, MESH_PASSWORD, &scheduller, MESH_PORT, WIFI_AP_STA,
               MESH_CHANNEL);

    Serial.println(F("CONECTION MANAGER -> Setting Up OnReceive Callback "));
    mesh->onReceive([this](const uint32_t &from, const String &msg) {
      Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
      mqttClient->publish(GATEWAY_OUTPUT_NODES_TOPIC.c_str(), msg.c_str());
    });

    Serial.println(F("CONECTION MANAGER -> Coneccting to Internet "));
    mesh->stationManual(STATION_SSID, STATION_PASSWORD);

    Serial.println(F("CONECTION MANAGER -> Setting up Hostname "));
    mesh->setHostname(HOSTNAME);

    bridgeACK->enable();
    mqttBrokerConnection->enable();

  };
}

ConectionManager::~ConectionManager() { mesh->stop(); }

void ConectionManager::loop() { mqttClient->loop(); }

IPAddress ConectionManager::getlocalIP() {
  return IPAddress(mesh->getStationIP());
}
