#ifndef WTRFLOW_HPP
#define WTRFLOW_HPP

//#define WTRFLOW_DEBUG 5

#include "Arduino.h"

class sensorWtrFlow_c
{
    private: /*Variables*/
        uint8_t  PulseInputPin;
        uint16_t PulseInputRaw;
        uint16_t PulseInputRawMax_CL;
        uint16_t PulseInputRawMin_CL;
    public: /*Variables*/

    public: /*Methods*/
        boolean init(uint8_t);
        void cyclic();
    private: /*Methods*/
        uint16_t ReadRaw();      
};



#endif