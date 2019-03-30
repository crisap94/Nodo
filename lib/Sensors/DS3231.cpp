///////////////////////////////////////////////////////////
//  DS3231.cpp
//  Implementation of the Class DS3231
//  Created on:      28-Mar-2019 4:29:34 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "DS3231.h"
#include "Arduino.h"

DS3231 *DS3231::m_ds3231 = NULL;

DS3231::DS3231(){

}

DS3231::~DS3231(){

}

long DS3231::getValue(){
	long epoch = 0;
	return epoch;
}

