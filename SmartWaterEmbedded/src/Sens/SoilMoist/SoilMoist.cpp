#include "SoilMoist.hpp"
#include "DebugFunction.hpp"

void sensorSoilMoist_c::cyclic()
{
    SimpleSoilStatus = CalculateSimpleSoilStatus(ReadRaw());
}
/**
 * @brief (Public) Initialize sensor with the correct analog pin
 * 
 * @param AnalogPin uint8_t analog pin provided by variant.h
 * @return boolean true if initialized ok false if not
 */
boolean sensorSoilMoist_c::init(uint8_t AnalogPin)
{
    AnalogInputPin = AnalogPin;
    /* TODO: Implement logic to check sensor (short to gnd short to VCC) */
    return true;
}

uint16_t sensorSoilMoist_c::ReadRaw()
{
    AnalogInputRaw = analogRead(AnalogInputPin);
#ifdef DEBUG_ENABLED
    Serial.print("Raw Soil Moisture is: ");
    Serial.println(AnalogInputRaw);
#endif
    return AnalogInputRaw;
}

SimpleSoilStatus_e sensorSoilMoist_c::CalculateSimpleSoilStatus(uint16_t RawInput)
{
    SimpleSoilStatus_e ret_val = SOIL_DRY;

    if(RawInput >= DryThreshold_CL && RawInput <= HumidThreshold_CL)
    {
        ret_val = SOIL_HUMID;
    }
    else if (RawInput >= HumidThreshold_CL)
    {
        ret_val = SOIL_WET;
    }

    return ret_val;
}
/**
 * @brief Set the threshold for the RAW data to calculate the SoilStatus
 * 
 * @param DryThresh - Threshhold between DRY and HUMID
 * @param HumidThresh - Threshold between HUMID and WET
 */
void sensorSoilMoist_c::setThresholds(uint16_t DryThresh, uint16_t HumidThresh)
{
    DryThreshold_CL = DryThresh;
    HumidThreshold_CL = HumidThresh;
}
/**
 * @brief Delivers the soil status
 * 
 * @return SimpleSoilStatus_e - Soil status (DRY, HUMID, WET)
 */
SimpleSoilStatus_e sensorSoilMoist_c::getSimpleSoilStatus()
{
    return SimpleSoilStatus;
}