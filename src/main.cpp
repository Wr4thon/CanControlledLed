#include <receiver/receiver.h>

#ifdef RECEIVER
receiver *m = new receiver();

void canInt()
{
  Serial.println("interrupt");

  if (m == NULL)
  {
    Serial.println("module was null");
  }

  m->setCanInterruptFlag(1);
}
#else
sender *m = new sender();

#endif

void setup()
{
  Serial.begin(9600);
  while (!Serial && 5000 > millis())
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
