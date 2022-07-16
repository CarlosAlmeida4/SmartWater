#ifndef PHOTORES_HPP
#define PHOTORES_HPP

//#define PHOTORES_DEBUG 2

#include "Arduino.h"

typedef enum 
{
    NIGHT,
    DAWN_DUSK,
    CLOUDY,
    CLEAR
}SensorPhotoRes_e;

class sensorPhotoRes_c
{   
    private: /*Variables*/
        uint8_t AnalogInputPin;
        uint16_t AnalogInputRaw;
        uint16_t AnalogInputRawMax_CL;
        uint16_t AnalogInputRawMin_CL;
        uint16_t LightLevelTrsh_CL[4]; 
        
    public: /*Variables*/
        SensorPhotoRes_e ActualLightLevel;

    public: /*Methods*/
        boolean init(uint8_t);
        void cyclic();

    private: /*Methods*/
        uint16_t ReadRaw();  
        void updateSunlight();    
};

#endif