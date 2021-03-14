// with changing the include from 'receiver' to 'sender' I can change most of
// the code without needing to create a second platformIO project.
#include <receiver/receiver.h>
//#include <sender/sender.h>

#ifdef RECEIVER
receiver *m = new receiver();

/**
 * canInt is a method, that gets attached to a Interrupt pin so the MCP2515
 * can signal the microcontroller that a new message is available for reading
*/
void canInt()
{
  Serial.println("interrupt");

  if (m == NULL)
  {
    Serial.println("module was null");
  }

  m->setMessageAvailable();
}
#else
sender *m = new sender();
#endif

void setup()
{
  Serial.begin(9600);
  while (!Serial && (5000 > millis()))
    ;

  m->setup();

#ifdef RECEIVER
  attachInterrupt(INT0, canInt, FALLING);
#endif
}

void loop()
{
  m->loop();
}
