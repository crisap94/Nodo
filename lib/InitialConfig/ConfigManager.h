///////////////////////////////////////////////////////////
//  ConfigManager.h
//  Implementation of the Class ConfigManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_)
#define EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_

#include "ESP8266WiFi.h"

#include "ESP8266HTTPClient.h"

#ifndef STASSID
#define STASSID "smavagpsserver"
#define STAPSK "smava1234"
#endif

class ConfigManager {

public:
  const char *ssid = STASSID;
  const char *password = STAPSK;

  HTTPClient *http;
  ConfigManager();
  virtual ~ConfigManager();

  void connectGPSServer();
  void getInitialConfigData();
  bool isConfig();
  void reset();
};
#endif // !defined(EA_11E06D4D_4D21_4530_9700_8484EA67C5A8__INCLUDED_)
