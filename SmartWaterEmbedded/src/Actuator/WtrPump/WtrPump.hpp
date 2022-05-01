#ifndef WTRPUMP_HPP
#define WTRPUMP_HPP

#define ACTUATOR_DEBUG 7

#include "Arduino.h"

typedef enum 
{
    OPENING,
    CLOSING,
    OPEN,
    CLOSED,
    INVALID
}PumpStatus_e;

class ActuatorWtrPump_c
{   
    private: /*Variables*/
        uint8_t controlPinA;
        uint8_t controlPinB;
        uint8_t enablePin;
        PumpStatus_e PumpStatus;
        uint8_t PWMdutyCycle;
    public: /*Variables*/
        PumpStatus_e PumpStatusRequest;
    public: /*Methods*/
        boolean init(uint8_t,uint8_t,uint8_t);
        void cyclic();
        void Open();
        void Close();
        void setPWMduty(uint8_t);
        void Stop();
    private: /*Methods*/
            
};


#endif