#include "PhotoRes.hpp"
#include "DebugFunction.hpp"

void sensorPhotoRes_c::cyclic()
{
    ReadRaw();
    updateSunlight();
}
/**
 * @brief (Public) Initialize sensor with the correct analog pin
 * 
 * @param AnalogPin uint8_t analog pin provided by variant.h
 * @return boolean true if initialized ok false if not
 */
boolean sensorPhotoRes_c::init(uint8_t AnalogPin)
{
    AnalogInputPin = AnalogPin;
    /* TODO: Implement logic to check sensor (short to gnd short to VCC) */
    /* TODO: Implement NvM storage for calibratables */
    
    LightLevelTrsh_CL[NIGHT]    = 50;
    LightLevelTrsh_CL[DAWN_DUSK]= 100;
    LightLevelTrsh_CL[CLOUDY]   = 175;
    LightLevelTrsh_CL[CLEAR]    = 250;
    
    return true;
}

uint16_t sensorPhotoRes_c::ReadRaw()
{
    AnalogInputRaw = analogRead(AnalogInputPin);
#ifdef DEBUG_ENABLED
    Serial.print("Raw PhotoResistor is: ");
    Serial.println(AnalogInputRaw);
#endif
}

void sensorPhotoRes_c::updateSunlight()
{
    if(AnalogInputRaw <= LightLevelTrsh_CL[NIGHT])
    {
        ActualLightLevel = NIGHT;
    }
    else if(AnalogInputRaw > LightLevelTrsh_CL[NIGHT] && AnalogInputRaw <= LightLevelTrsh_CL[DAWN_DUSK])
    {
        ActualLightLevel = DAWN_DUSK;
    }
    else if(AnalogInputRaw > LightLevelTrsh_CL[DAWN_DUSK] && AnalogInputRaw <= LightLevelTrsh_CL[CLOUDY])
    {
        ActualLightLevel = CLOUDY;
    }
    else if(AnalogInputRaw > LightLevelTrsh_CL[CLOUDY])
    {
        ActualLightLevel = CLEAR;
    }
}  
