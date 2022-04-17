#include <Arduino.h>
#include "SchM/SchM.hpp"

using namespace arduino;

void setup() {
  // put your setup code here, to run once:
  SchM_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  SchM_Main();
}