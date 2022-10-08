#ifndef WATERINGCONTROLLER_HPP
#define WATERINGCONTROLLER_HPP

#define WATERINGCONTROLLER_DEBUG 10

#define START_SECONDS 10
#define START_MINUTES 00
#define START_HOURS 00
#define WATERING_INTERVAL 30

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
        /* Change these values to set the current initial time */
        const byte seconds = 0;
        const byte minutes = 30;
        const byte hours = 18;
        /* Change these values to set the current initial date */
        const byte day = 26;
        const byte month = 7;
        const byte year = 22;
        byte EndSeconds;
        byte EndMinutes;
        byte EndHours;
    public: /*Variables*/
        WateringControllerStateMachine_e WateringControllerStateMachine = INIT;
        typedef struct AlarmTime
        {
            uint8_t StartHour;
            uint8_t StartMinute;
            uint8_t StartSecond;
            uint8_t duration;
        }alarmTime;
    public: /*Methods*/
        void cyclic();
        void setAlarmTime(AlarmTime *);
    private: /*Methods*/
        void print2digits(int);
        void printDate();
        void printTime();

};

#endif 