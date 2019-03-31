#include "ESP8266WiFi.h"
#include "painlessMesh.h"
#include "DataManager.h"
#include "ArduinoJson.h"

#define MESH_PREFIX "smava"
#define MESH_PASSWORD "smava1234"
#define MESH_PORT 5555

Scheduler userScheduler; // to control your personal task
painlessMesh mesh;
DataManager *m_dataManager;

// Prototype
void receivedCallback(uint32_t from, String &msg);

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(5000, TASK_FOREVER, []() {

  
  String json = m_dataManager->getJSON();

  Serial.println("Sending JSON");
  if (logServerId == 0) // If we don't know the logServer yet
    mesh.sendBroadcast(json);
  else
    mesh.sendSingle(logServerId, json);
});

void setup() {
  Serial.begin(115200);

  m_dataManager = new DataManager();

  mesh.setDebugMsgTypes(
      ERROR | STARTUP |
      CONNECTION); // set before init() so that you can see startup messages

  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA,
            6);
  mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
  userScheduler.addTask(myLoggingTask);
  myLoggingTask.enable();
}

void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
}

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

  const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, msg);

  if (doc.containsKey("topic"))
  {
    if (String("logServer").equals(doc["topic"].as<String>()))
    {
      // check for on: true or false
      logServerId = doc["nodeId"];
      Serial.printf("logServer detected!!!\n");
    }
    Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
  }
}
