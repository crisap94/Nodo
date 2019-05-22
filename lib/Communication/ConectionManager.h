///////////////////////////////////////////////////////////
//  ConectionManager.h
//  Implementation of the Class ConectionManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
#define EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <ESP8266WiFi.h>

#include "painlessMesh.h"

#include "DataManager.h"

#define MESH_PREFIX "smava"
#define MESH_PASSWORD "smava1234"
#define MESH_PORT 5555
#define MESH_CHANNEL 4


class ConectionManager {

public:

  ConectionManager();
  virtual ~ConectionManager();
  
  Task *tMesh;

  std::function<void()> initMesh;
  std::function<void()> sendMessage;

  void loop();

private:
  uint32_t gatewayId;

  Task *tSendMessage;

  painlessMesh *mesh;

  DataManager *m_dataManager;
};
#endif // !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
