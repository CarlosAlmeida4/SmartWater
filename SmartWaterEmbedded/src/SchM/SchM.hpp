#ifndef SCHM_HPP
#define SCHM_HPP

#include "Sens\Sens.hpp"

#define _TASK_SLEEP_ON_IDLE_RUN
#define SCHM_DEBUG 0

#define TASK100MS_PERIOD  100
#define TASK1000MS_Period   1000
#define TASK2000MS_Period   2000


void SchM_Init(void);
void SchM_Main(void);

#endif