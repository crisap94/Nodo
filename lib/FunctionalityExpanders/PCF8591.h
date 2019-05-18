///////////////////////////////////////////////////////////
//  PCF8591.h
//  Implementation of the Class pcf8591
//  Created on:      28-Mar-2019 4:29:36 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
#define EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_

#include "Arduino.h"
#include "Wire.h"

#include "I2C.h"

// Uncomment to enable printing out nice debug messages.
// #define PCF8591_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef PCF8591_DEBUG
	#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
	#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
	#define DEBUG_PRINT(...) {}
	#define DEBUG_PRINTLN(...) {}
#endif

#include <math.h>

#define AIN0 B00000000
#define AIN1 B00000001
#define AIN2 B00000010
#define AIN3 B00000011

#define CHANNEL0 B00000000
#define CHANNEL1 B00000001
#define CHANNEL2 B00000010
#define CHANNEL3 B00000011

#define AUTOINCREMENT_READ B00000100

#define SINGLE_ENDED_INPUT B00000000
#define TREE_DIFFERENTIAL_INPUT B00010000
#define TWO_SINGLE_ONE_DIFFERENTIAL_INPUT B00100000
#define TWO_DIFFERENTIAL_INPUT B00110000

#define ENABLE_OUTPUT B01000000
#define DISABLE_OUTPUT B01000000

#define OUTPUT_MASK B01000000

class PCF8591 : public I2C {
private:
  static PCF8591 *m_pcf8591;

  int _address;
  int _scl;
  int _sda;
  PCF8591();
  PCF8591(uint8_t address);

  byte _outputStatus = DISABLE_OUTPUT;

  long readVcc(void);

  virtual ~PCF8591();

public:
  struct AnalogInput {
    uint8_t ain0;
    uint8_t ain1;
    uint8_t ain2;
    uint8_t ain3;
  } analogInput;

  enum PIN {
    /**
     * @brief
     * * Pins from PCF8591
     *
     */
    BATT_TEMPERATURE_VOLTAJE = 2 ,
    BATT_VOLTAJE = 0,
    SOIL_HUMIDITY_VOLTAJE = 3,
    PANEL_VOLTAJE = 1,
  };
  static PCF8591 *getInstance() {
    if (m_pcf8591 == NULL) {
      m_pcf8591 = new PCF8591(0x48);
    }

    return m_pcf8591;
  }

  void begin(void);

  AnalogInput analogReadAll(byte readType = SINGLE_ENDED_INPUT);

  uint8_t analogRead(uint8_t channel, byte readType = SINGLE_ENDED_INPUT);

  void analogWrite(uint8_t value);

  void voltageWrite(float value, bool microcontrollerReferenceVoltage = true,
                    float referenceVoltage = 3.3);

  float voltageRead(uint8_t analogPin,
                    bool microcontrollerReferenceVoltage = true,
                    float referenceVoltage = 3.3);

  float getValue(PCF8591::PIN _pin);
};
#endif // !defined(EA_93B99A19_88B0_4301_B371_8E3190620A74__INCLUDED_)
