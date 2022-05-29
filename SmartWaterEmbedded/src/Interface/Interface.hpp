#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#define INTERFACE_DEBUG 10

#include "Arduino.h"
#include "Actuator/Actu.hpp"

void WifiAPI2Actuator_SetValveOpen(void);
void WifiAPI2Actuator_SetValveClosed(void);

#endif 