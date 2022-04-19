#include "WtrFlow.hpp"
#include "DebugFunction.hpp"

void sensorWtrFlow_c::cyclic()
{
    ReadRaw();
}
/**
 * @brief (Public) Initialize sensor with the correct analog pin
 * 
 * @param PulsePin uint8_t analog pin provided by variant.h
 * @return boolean true if initialized ok false if not
 */
boolean sensorWtrFlow_c::init(uint8_t PulsePin)
{
    PulseInputPin = PulsePin;
    pinMode(PulseInputPin, INPUT);
    /* TODO: Implement logic to check sensor (short to gnd short to VCC) */
    return true;
}

uint16_t sensorWtrFlow_c::ReadRaw()
{
    PulseInputRaw = pulseIn(PulseInputPin, HIGH);
#ifdef DEBUG_ENABLED
    Serial.print("Raw WaterFlow is: ");
    Serial.println(PulseInputRaw);
#endif
}
