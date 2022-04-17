#ifndef DEBUGFUNCTIONS_HPP
#define DEBUGFUNCTIONS_HPP

#include "Arduino.h"

#define DEBUG_ENABLED

#ifndef SCHM_DEBUG
#define SCHM_DEBUG 0
#endif



inline void debugPrint(int moduleID,String debugMessage)
{
#ifdef DEBUG_ENABLED
    Serial.print("Module ID: ");
    Serial.print(moduleID);
    Serial.print(" Debug: ");
    Serial.println(debugMessage);
#endif
}


#endif