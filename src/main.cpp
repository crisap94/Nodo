#include "ESP8266WiFi.h"
#include "painlessMesh.h"
#include "DataManager.h"

#define MESH_PREFIX "whateverYouLike"
#define MESH_PASSWORD "somethingSneaky"
#define MESH_PORT 5555

Scheduler userScheduler; // to control your personal task
painlessMesh mesh;
DataManager *m_dataManager;

// Prototype
void receivedCallback(uint32_t from, String &msg);

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(10000, TASK_FOREVER, []() {
  String json = String(m_dataManager->getJSON());
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
}
