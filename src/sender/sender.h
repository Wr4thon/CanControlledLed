#pragma once

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

class sender
{
private:
  // pin the button is connected to.
  uint8_t ledPin;
  // CS pin of mcp2515
  uint8_t canCsPin;

  // time before checking the state of the button again after a change.
  unsigned long debounceTime;

  MCP_CAN *can; // The can bus.

  unsigned long lastStateChange;
  int lastState = LOW;
  byte ledTransmitState;

public:
  sender() : sender(9, 10, 100) {}
  sender(uint8_t buttonPin, uint8_t canCsPin, unsigned long debounceTime);

  ~sender();

  /**
   * setup contains the setup logic for the sender module.
  */
  void setup();

  /**
   * loop contains the loop logic for the sender module.
  */
  void loop();

  /**
   * InitializeCAN initializes the can object, than begins the communication.
   * It loops for as long as it needs til the mcp2515 returns CAN_OK (0x00).
   * This might block the Arduino from  continuing, but that is ok as 
   * We can not use it anyways with an uninitialized can bus.
  */
  void initializeCAN();
};
