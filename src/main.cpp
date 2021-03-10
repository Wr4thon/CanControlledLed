#include <sender/module.h>

module *s = new module();

void setup()
{
  s->setup();
}

void loop()
{
  s->loop();
}