#ifndef ACTU_HPP
#define ACTU_HPP

//#define ACTUATOR_DEBUG 6

#include "WtrPump/WtrPump.hpp"

void ActuatorsInit(void);
void Actu2s(void);
void Actu1s(void);
void Actu100ms(void);
void Actu10ms(void);
void Actu1ms(void);
void ActuSetValveOpen(void);
void ActuSetValveClosed(void);
#endif