///////////////////////////////////////////////////////////
//  PCF8574.cpp
//  Implementation of the Class PCF8574
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "PCF8574.h"

PCF8574 *PCF8574::m_pcf8574 = NULL;

PCF8574::PCF8574() {}

PCF8574::~PCF8574() {}

void PCF8574::begin(){

}

boolean PCF8574::getValue(PCF8574::PIN _pin) {
  boolean value = -1;
  switch (_pin) {
  case PCF8574::PIN::TP4056_CHRG_STATUS:
    value = true;
    /**
   * @brief
   * TODO Set function to get the pin status from the PCF8574
   *
   */
    break;

  case PCF8574::PIN::TP4056_STDBY:
    value = false;
    /**
   * @brief
   * TODO Set function to get the pin status from the PCF8574
   *
   */
    break;
  }
  return value;
}

void PCF8574::setValue(PCF8574::PIN _pin, boolean value) {
  switch (_pin) {
  case PCF8574::PIN::TP4056_ENABLE:
  /**
   * @brief 
   * TODO Set function to set the pin status from the PCF8574
   * 
   */
    break;

  case PCF8574::PIN::RT9013_ENABLE:
      /**
   * @brief 
   * TODO Set function to set the pin status from the PCF8574
   * 
   */
      break;
  }
}