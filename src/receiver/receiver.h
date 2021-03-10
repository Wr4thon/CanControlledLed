#pragma once

#define RECEIVER

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

class receiver
{
private:
  // pin the button is connected to.
  uint8_t ledPin;
  // CS pin of mcp2515
  uint8_t canCsPin;

  MCP_CAN *can; // The can bus.

  unsigned long lastStateChange;
  int lastState = LOW;
  byte ledTransmitState;

  unsigned char canInterruptFlag;

public:
  receiver() : receiver(9, 10) {}
  receiver(uint8_t ledPin, uint8_t canCsPin);

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

  void setCanInterruptFlag(byte value);
};
