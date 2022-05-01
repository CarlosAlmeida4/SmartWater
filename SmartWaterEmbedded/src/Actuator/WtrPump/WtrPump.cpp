#include "WtrPump.hpp"
#include "DebugFunction.hpp"

void ActuatorWtrPump_c::cyclic()
{
    switch (PumpStatusRequest)
    {
    case OPENING:
        Open();       
        break;
    case CLOSING:
        Close();
        break;
    case OPEN:
        Stop();
        break;
    case CLOSED:
        Stop();
        break;
    }
    PumpStatus = PumpStatusRequest;
    //#ifdef DEBUG_ENABLED
    //#ifdef ACTUATOR_DEBUG
    Serial.print("------Current pump state: ");
    Serial.println(PumpStatus);
    //#endif
    //#endif
}

/**
 * @brief initializes the actuator based on the LD293 Hbridge
 * 
 * @param controlPin_a High side control pin
 * @param controlPin_b Low side control pin
 * @param enablepin overall bridge control to set PWM
 * @return boolean false if initialization was not successful
 */
boolean ActuatorWtrPump_c::init(uint8_t controlPin_a,uint8_t controlPin_b,uint8_t enablepin)
{
    controlPinA = controlPin_a;
    controlPinB = controlPin_b;
    enablePin = enablepin;

    pinMode(controlPinA,OUTPUT);
    pinMode(controlPinB,OUTPUT);
    pinMode(enablePin,OUTPUT);
    /* TODO: Implement logic to check actuator (short to gnd short to VCC) 
    * Implement routine to check that pump is closed (maybe TODO in higher layer module)
    */
    PumpStatus = (PumpStatus_e)CLOSED;
    PumpStatusRequest =  (PumpStatus_e)CLOSED;
    return true;
}

void ActuatorWtrPump_c::Open()
{
    digitalWrite(controlPinA, HIGH);
    digitalWrite(controlPinB, LOW);
    analogWrite(enablePin,PWMdutyCycle);
}


void ActuatorWtrPump_c::Close()
{
    digitalWrite(controlPinA, LOW);
    digitalWrite(controlPinB, HIGH);
    analogWrite(enablePin,PWMdutyCycle);   
}

void ActuatorWtrPump_c::setPWMduty(uint8_t requestDuty)
{
    PWMdutyCycle = requestDuty;
}

void ActuatorWtrPump_c::Stop()
{
    digitalWrite(controlPinA, LOW);
    digitalWrite(controlPinB, LOW);
    analogWrite(enablePin,PWMdutyCycle);   
}