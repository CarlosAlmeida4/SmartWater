#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "Arduino.h"
#include "PhotoRes\PhotoRes.hpp"
#include "SoilMoist\SoilMoist.hpp"
#include "TemHum\TemHum.hpp"
#include "WtrFlow\WtrFlow.hpp"


#define SENSORS_DEBUG 1

void SensorsInit(void);
void Sens2s(void);
void Sens1s(void);
void Sens100ms(void);
void Sens10ms(void);
void Sens1ms(void);

#endif