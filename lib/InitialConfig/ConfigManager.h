///////////////////////////////////////////////////////////
//  ConfigManager.h
//  Implementation of the Class ConfigManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_)
#define EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_

#include "ESP8266WiFi.h"

#define DEBUG_ESP_HTTP_CLIENT
#define DEBUG_ESP_PORT
#include "ESP8266HTTPClient.h"

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

/* #define STASSID "smavagpsserver"
#define STAPSK "smava1234" */
#define STASSID "Apto402"
#define STAPSK "makairaapartamento402"

#define CONNECT_TIMEOUT 50   // Seconds
#define CONNECT_OK 0         // Status of successful connection to WiFi
#define CONNECT_FAILED (-99) // Status of failed connection to WiFi

#define EPOCH_19_1_1 1546300800
#define NOT_CONFIGURED "notConfigured"
#define NOT_SET -1
#define DEFAULT_REFRESH_WINDOW 5

class ConfigManager {

public:
  struct Config {
    char zoneId[64] = NOT_CONFIGURED;
    uint64_t epoch = EPOCH_19_1_1;
    int32 latitud = NOT_SET;
    int32 longitud = NOT_SET;
    uint8_t refreshWindow = DEFAULT_REFRESH_WINDOW;
  } config;

  const char *ssid = STASSID;
  const char *password = STAPSK;

  Task *tConnect;

  HTTPClient *http;
  String response;
  uint8_t SpiffCounter = 0;
  


  ConfigManager();
  virtual ~ConfigManager();

  bool begin();
  void end();
  bool isConfig();
  void reset();

  private:


  std::function<void()> connectToGPSServer;
  std::function<void()> connectCheck;
  std::function<void()> requestFromGPS;
  std::function<void()> updateTime;
  std::function<void()> saveConfig;
  
  std::function<void()> loadConfig;
};
#endif // !defined(EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_)
