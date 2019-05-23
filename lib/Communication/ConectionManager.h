///////////////////////////////////////////////////////////
//  ConectionManager.h
//  Implementation of the Class ConectionManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
#define EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_

#include <Scheduller.hpp>

#include "painlessMesh.h"




class ConectionManager {


public:

  ConectionManager();
  virtual ~ConectionManager();
  
  Task *tMesh;
  Task *tSendMessage;

  std::function<void()> initMesh;
  std::function<void()> sendMessage;

  

  void loop();

private:


};
#endif // !defined(EA_995858AF_5C4C_4f8f_AC9F_9715CA0F757F__INCLUDED_)
