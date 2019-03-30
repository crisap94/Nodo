///////////////////////////////////////////////////////////
//  VEML6075.cpp
//  Implementation of the Class VEML6075
//  Created on:      28-Mar-2019 4:29:38 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "VEML6075.h"
#include "Arduino.h"

VEML6075 *VEML6075::m_veml6075 = NULL;

VEML6075::VEML6075() {}

VEML6075::~VEML6075() {}

float VEML6075::getValue() {
  randomSeed(analogRead(A0));
  return random(600, 700);
}