///////////////////////////////////////////////////////////
//  VEML6030.cpp
//  Implementation of the Class VEML6030
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "VEML6030.h"
#include "Arduino.h"

VEML6030 *VEML6030::m_veml6030 = NULL;

VEML6030::VEML6030() {}

VEML6030::~VEML6030() {}

float VEML6030::getValue() {
  randomSeed(analogRead(A0));
  return random(600, 700);
}
