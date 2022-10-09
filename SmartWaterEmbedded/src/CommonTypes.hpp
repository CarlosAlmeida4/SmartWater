#ifndef COMMONTYPES_HPP
#define COMMONTYPES_HPP

#include "Arduino.h"

struct AlarmTime
{
    uint8_t StartHour;
    uint8_t StartMinute;
    uint8_t StartSecond;
    uint16_t duration;
};

#endif