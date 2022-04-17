#include "PhotoRes.hpp"
#include "DebugFunction.hpp"

void sensorPhotoRes_c::cyclic()
{
    ReadRaw();
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

