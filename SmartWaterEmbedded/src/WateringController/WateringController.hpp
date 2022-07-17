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
    ERROR
}WateringControllerStateMachine_e;

class WateringController_c
{
    private: /*Variables*/
        /* Create an rtc object */
        RTCZero rtc;
    public: /*Variables*/
        WateringControllerStateMachine_e WateringControllerStateMachine = INIT;
    public: /*Methods*/
        void cyclic();
    private: /*Methods*/

};

#endif 