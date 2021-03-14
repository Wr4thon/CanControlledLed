#pragma once

#define RECEIVER

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

class receiver
{
private:
  // Pin the LED is connected to.
  uint8_t ledPin;
  // CS pin of MCP2515
  uint8_t canCsPin;

  // reference to the CAN object
  MCP_CAN *can; 

  unsigned long lastStateChange;
  int lastState = LOW;
  byte ledTransmitState;

  /**
   * when set to true the loop attempts to read a message from the CAN module
  */
  volatile bool canInterruptFlag;

  /**
   * resetInterruptFlag resets the canInterruptFlag.
  */
  void resetInterruptFlag();

public:
  /**
   * default ctor
  */
  receiver() : receiver(9, 10) {}

  /**
   * ctor
   * @param ledPin a pin to which an LED is connected.
   * @param canCsPin the chip select pin for the MCP2515.
  */
  receiver(uint8_t ledPin, uint8_t canCsPin);

  /**
   * destructor
  */
  ~receiver();

  /**
   * setup contains the setup logic for the receiver module.
  */
  void setup();

  /**
   * loop contains the loop logic for the receiver module.
  */
  void loop();

  /**
   * InitializeCAN initializes the can object, than begins the communication.
   * It loops for as long as it needs til the mcp2515 returns CAN_OK (0x00).
   * This might block the Arduino from  continuing, but that is ok as 
   * We can not use it anyways with an uninitialized can bus.
  */
  void initializeCAN();

  /**
   * setMessageAvailable tells the class that new data is 
   * available for reading from the module.
  */
  void setMessageAvailable();
};
