#include <sender/module.h>

module::module(uint8_t buttonPin,
               uint8_t canCsPin,
               unsigned long serialStartupTimeout,
               unsigned long debounceTime)
{
  this->buttonPin = buttonPin;
  this->canCsPin = canCsPin;
  this->serialStartupTimeout = serialStartupTimeout;
  this->debounceTime = debounceTime;
}

void module::initializeCAN()
{
  // initialize the CAN bus with
  can = new MCP_CAN(canCsPin);
  unsigned long start = millis();
  Serial.print("Begin can ");

  while (CAN_OK != can->begin(CAN_125KBPS, MCP_8MHz))
  {
    Serial.print(".");
  }

  Serial.println();
  Serial.print("can initialized. took: ");
  Serial.print((millis() - start));
  Serial.println("ms");
  Serial.println();
}

void module::setup()
{
  Serial.begin(9600);
  while (!Serial && serialStartupTimeout > millis())
    ;

  initializeCAN();

  pinMode(buttonPin, INPUT_PULLUP);
}

void module::loop()
{
  if ((millis() - lastStateChange) < debounceTime)
  {
    // Not enough time passed since the last button change.
    // Just wait a couple of ms to make sure to not spam on the bus.
    // If you want to know more on why I'm doing this google for 'debounce'.
    return;
  }

  int currentState = digitalRead(buttonPin);
  if (currentState == lastState)
  {
    // State did not change, nothing to do.
    return;
  }

  lastStateChange = millis();
  lastState = currentState;
  if (currentState)
  {
    // Button is currently not pressed.
    // We only want to send a message when the button is pressed.
    return;
  }

  // toggle the ledTransmitState
  ledTransmitState = !ledTransmitState;
  Serial.print("button pressed; sending: ");
  Serial.println(ledTransmitState);

  // Set the new ledTransmitState in the buffer and send the message.
  byte buf[1] = {ledTransmitState};
  can->sendMsgBuf(2, 0, 1, buf);
}

module::~module()
{
  can = NULL;
}
