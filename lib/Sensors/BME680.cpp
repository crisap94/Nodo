///////////////////////////////////////////////////////////
//  BME680.cpp
//  Implementation of the Class BME680
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#include "BME680.h"
#include "Arduino.h"

BME680 *BME680::m_BME680 = NULL;

/**
 * @brief Construct a new BME680::BME680 object
 * TODO Debug message constructing the BME680
 * 
 */
BME680::BME680(){
	
}

/**
 * @brief Destroy the BME680::BME680 object
 * TODO Debug Message destroying the BME680
 * 
 */
BME680::~BME680(){

}

/**
 * * Initilize the Sensor
 * TODO Implement Wire to Initilize the I2C BUS
 * 
 */
void BME680::begin(){

}

float BME680::getHumidity(){
	int seed = analogRead(A0);
	randomSeed(seed);
	float hum = random(80,90);
	return hum;
}
float BME680::getTemperature(){
	int seed = analogRead(A0);
	randomSeed(seed);
	float temp = random(29, 31);
	return temp;
}
float BME680::getVOC(){
	int seed = analogRead(A0);
	randomSeed(seed);
	float voc = random(600, 700);
	return voc;
}
float BME680::getPressure(){
	int seed = analogRead(A0);
	randomSeed(seed);
	float press = random(1000, 1020);
	return press;
}
