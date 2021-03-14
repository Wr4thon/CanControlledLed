#include <receiver/receiver.h>

receiver::receiver(uint8_t ledPin, uint8_t canCsPin)
{
  this->ledPin = ledPin;
  this->canCsPin = canCsPin;
  resetInterruptFlag();
}

void receiver::initializeCAN()
{
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

void receiver::setup()
{
  initializeCAN();

  pinMode(ledPin, OUTPUT);
}

void receiver::loop()
{
  if (!canInterruptFlag)
  {
    return;
  }

  Serial.print("received: ");
  resetInterruptFlag();

  byte len = 0;
  byte buf[8];
  can->readMsgBuf(&len, buf);

  for (int i = 0; i < len; i++)
  {
    Serial.print(buf[i]);
    Serial.print("\t");
  }
  Serial.println();

  if (len != 1 || buf[0] > 1)
  {
    // expecting exactly one byte with value 1 or 0, so invalid, so skip.
    return;
  }

  digitalWrite(ledPin, buf[0]);
}

receiver::~receiver()
{
  can = NULL;
}

void receiver::setMessageAvailable()
{
  this->canInterruptFlag = true;
}

void receiver::resetInterruptFlag()
{
  canInterruptFlag = false;
}