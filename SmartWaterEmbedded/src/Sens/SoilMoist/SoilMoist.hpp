#ifndef SOILMOIST_HPP
#define SOILMOIST_HPP

#define SOILMOIST_DEBUG 3

#include "Arduino.h"

typedef enum 
{
    SOIL_DRY,
    SOIL_HUMID,
    SOIL_WET
}SimpleSoilStatus_e;

class sensorSoilMoist_c
{   
    private: /*Variables*/
        uint8_t AnalogInputPin;
        uint16_t AnalogInputRaw;
        /* See https://wiki.dfrobot.com/Moisture_Sensor__SKU_SEN0114_ 
        * For Threshold explanation
        */
        uint16_t DryThreshold_CL = 300; 
        uint16_t HumidThreshold_CL = 700;
        SimpleSoilStatus_e SimpleSoilStatus;
        
    public: /*Variables*/
        

    public: /*Methods*/
        boolean init(uint8_t);
        void cyclic();
        void setThresholds(uint16_t,uint16_t);
        SimpleSoilStatus_e getSimpleSoilStatus();
    private: /*Methods*/
        uint16_t ReadRaw();
        SimpleSoilStatus_e CalculateSimpleSoilStatus(uint16_t);
};

#endif