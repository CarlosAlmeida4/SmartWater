#include "SchM.hpp" //Own header include
#include "DebugFunction.hpp" 
#include <TaskScheduler.h>

Scheduler runner;
WateringController_c WateringController;

// Callback methods prototypes
void Task100MS();
void Task1000MS();
void Task2000MS();

// Tasks
Task t1(TASK100MS_PERIOD, TASK_FOREVER, &Task100MS, &runner, true);  //adding task to the chain on creation
Task t2(TASK1000MS_Period, TASK_FOREVER, &Task1000MS, &runner, true);  //adding task to the chain on creation
Task t3(TASK2000MS_Period, TASK_FOREVER, &Task2000MS, &runner, true);  //adding task to the chain on creation

void Task2000MS()
{
    Sens2s();
    Actu2s();
    Communication2s();
}

void Task100MS() { 
    Sens100ms();
    Actu100ms();
    //debugPrint(SCHM_DEBUG,"100MS task");
}

void Task1000MS(){
    Sens1s();
    Actu1s();
    WateringController.cyclic();
    //debugPrint(SCHM_DEBUG,"1000MS task");
}

void SchM_Init(void)
{
    /* Init debug serial */
    Serial.begin(9600);

    /* Init sensors */
    SensorsInit();
    ActuatorsInit();
    CommunicationInit();
    runner.startNow();
}
void SchM_Main(void)
{
    //Communication2s();
    runner.execute();
}