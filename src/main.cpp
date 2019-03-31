//************************************************************
// this is a simple example that uses the painlessMesh library to
// connect to a another network and relay messages from a MQTT broker to the
// nodes of the mesh network.
// To send a message to a mesh node, you can publish it to
// "painlessMesh/to/12345678" where 12345678 equals the nodeId.
// To broadcast a message to all nodes in the mesh you can publish it to
// "painlessMesh/to/broadcast".
// When you publish "getNodes" to "painlessMesh/to/gateway" you receive the mesh
// topology as JSON
// Every message from the mesh which is send to the gateway node will be
// published to "painlessMesh/from/12345678" where 12345678
// is the nodeId from which the packet was send.
//************************************************************

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <painlessMesh.h>
#include <ArduinoJson.h>

#define MESH_PREFIX "smava"
#define MESH_PASSWORD "smava1234"
#define MESH_PORT 5555

#define STATION_SSID "Apto402"
#define STATION_PASSWORD "makairaapartamento402"

#define HOSTNAME "MQTT_Bridge"

// Prototypes
void receivedCallback(const uint32_t &from, const String &msg);
void mqttCallback(char *topic, byte *payload, unsigned int length);

IPAddress getlocalIP();

IPAddress myIP(192, 168, 0, 150);
IPAddress mqttBroker(206, 189, 202, 242);

painlessMesh mesh;
WiFiClient wifiClient;
PubSubClient mqttClient;
Scheduler userScheduler; // to control your personal task

Task logServerTask(10000, TASK_FOREVER, []() {
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);

  doc["topic"] = "logServer";
  doc["nodeId"] = mesh.getNodeId();

  String str;
  serializeJson(doc, str);

  mesh.sendBroadcast(str);
});

void setup() {
  Serial.begin(115200);
  mqttClient.setClient(wifiClient);
  mqttClient.setServer(mqttBroker, 1883);
  mqttClient.setCallback(mqttCallback);

  mesh.setDebugMsgTypes(
      ERROR | STARTUP |
      CONNECTION); // set before init() so that you can see startup messages

  // Channel set to 6. Make sure to use the same channel for your mesh and for
  // you other
  // network (STATION_SSID)
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6);
  mesh.onReceive(&receivedCallback);

  mesh.stationManual(STATION_SSID, STATION_PASSWORD);
  mesh.setHostname(HOSTNAME);

  userScheduler.addTask(logServerTask);
  logServerTask.enable();
}

void loop() {
  mesh.update();
  mqttClient.loop();
  userScheduler.execute(); // it will run mesh scheduler as well

  if (myIP != getlocalIP()) {
    myIP = getlocalIP();
    Serial.println("My IP is " + myIP.toString());

    if (mqttClient.connect("painlessMeshClient", "smava", "12345678")) {
      Serial.println("Connected to Broker");
      mqttClient.publish("painlessMesh/from/gateway", "Ready!");
      mqttClient.subscribe("painlessMesh/to/#");
    }
  }
}

void receivedCallback(const uint32_t &from, const String &msg) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
  String topic = "painlessMesh/from/" + String(from);
  mqttClient.publish(topic.c_str(), msg.c_str());
}

void mqttCallback(char *topic, uint8_t *payload, unsigned int length) {
  char *cleanPayload = (char *)malloc(length + 1);
  payload[length] = '\0';
  memcpy(cleanPayload, payload, length + 1);
  String msg = String(cleanPayload);
  free(cleanPayload);

  String targetStr = String(topic).substring(16);

  if (targetStr == "gateway") {
    if (msg == "getNodes") {
      mqttClient.publish("painlessMesh/from/gateway",
                         mesh.subConnectionJson().c_str());
    }
  } else if (targetStr == "broadcast") {
    mesh.sendBroadcast(msg);
  } else {
    uint32_t target = strtoul(targetStr.c_str(), NULL, 10);
    if (mesh.isConnected(target)) {
      mesh.sendSingle(target, msg);
    } else {
      mqttClient.publish("painlessMesh/from/gateway", "Client not connected!");
    }
  }
}

IPAddress getlocalIP() { return IPAddress(mesh.getStationIP()); }
