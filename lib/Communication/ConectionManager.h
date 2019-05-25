///////////////////////////////////////////////////////////
//  ConectionManager.h
//  Implementation of the Class ConectionManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
#define EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_

#include <Scheduller.hpp>

#include <ESP8266WiFi.h>

#include "PubSubClient.h"

#include "painlessMesh.h"

#define MESH_PREFIX "smava"
#define MESH_PASSWORD "smava1234"
#define MESH_PORT 5555
#define MESH_CHANNEL 4

#define STATION_SSID "Apto402"
#define STATION_PASSWORD "makairaapartamento402"

#define HOSTNAME "MQTT_Bridge"

#define MQTT_PORT 1883
#define MQTT_USER "smava"
#define MQTT_PASSWORD "12345678"
#define MQTT_CLIENT "SMAVA Gateway"

class ConectionManager {


public:
  String GATEWAY_OUTPUT_NODES_TOPIC;
  String GATEWAY_OUTPUT_TOPIC;
  String GATEWAY_IN_TOPIC;

  ConectionManager();
  virtual ~ConectionManager();
  
  Task *tMesh;

  std::function<void()> initMesh;

  

  void loop();

private:
  IPAddress getlocalIP();

  Task *mqttBrokerConnection;
  Task *bridgeACK;

  IPAddress myIP;
  IPAddress MQTT_BROKER_IP;

  painlessMesh *mesh;
  WiFiClient *wifiClient;
  PubSubClient *mqttClient;
};
#endif // !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
