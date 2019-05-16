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

#include <ConectionManager.h>

#include <DataManager.h>

ConectionManager *m_conectionManager = new ConectionManager();


void setup() {
  Serial.begin(115200);
  m_conectionManager->begin();
}

void loop() {
  m_conectionManager->loop();
}
