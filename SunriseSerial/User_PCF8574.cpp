#include "User_PCF8574.h"

extern PCF8574 PCF_8574;

void doHigh(uint8_t Pin)
{
  PCF_8574.write(Pin, HIGH);
  int x = PCF_8574.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doLow(uint8_t Pin)
{
  PCF_8574.write(Pin, LOW);
  int x = PCF_8574.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doToggle(uint8_t Pin)
{
  PCF_8574.toggle(Pin);
  int x = PCF_8574.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
}
