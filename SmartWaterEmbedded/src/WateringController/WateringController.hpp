#ifndef WATERINGCONTROLLER_HPP
#define WATERINGCONTROLLER_HPP

#define WATERINGCONTROLLER_DEBUG 10

#include "Arduino.h"
#include "Interface/Interface.hpp"
#include "RTCZero.h"


typedef enum
{
    INIT,
    RUNNING,
    PRE_WATERING,
    WATERING,
    AFTER_WATERING,
    ERROR_WATERING
}WateringControllerStateMachine_e;

class WateringController_c
{
    private: /*Variables*/
        /* Create an rtc object */
        RTCZero rtc;
        /* Change these values to set the current initial time */
        const byte seconds = 0;
        const byte minutes = 30;
        const byte hours = 18;
        /* Change these values to set the current initial date */
        const byte day = 26;
        const byte month = 7;
        const byte year = 22;
    public: /*Variables*/
        WateringControllerStateMachine_e WateringControllerStateMachine = INIT;
    public: /*Methods*/
        void cyclic();
    private: /*Methods*/
        void print2digits(int);
        void printDate();
        void printTime();

};

#endif 