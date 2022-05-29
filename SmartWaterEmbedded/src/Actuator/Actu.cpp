#include "Actu.hpp"
#include "DebugFunction.hpp"

static ActuatorWtrPump_c ActuatorWtrPump; 

//#define SERIAL_COMMAND

void ActuatorsInit(void)
{
    ActuatorWtrPump.init(4,7,3);
    ActuatorWtrPump.setPWMduty(245);
}
void Actu2s(void)
{

}
void Actu1s(void)
{
    if(Serial.available())
    {
        #ifdef SERIAL_COMMAND
        char recv; 
        Serial.readBytes(&recv,1);
        #ifdef DEBUG_ENABLED
        #ifdef ACTUATOR_DEBUG
        Serial.print("Received char: ");
        Serial.println(recv);
        Serial.print("PumpStatusRequest: ");
        Serial.println(ActuatorWtrPump.PumpStatusRequest);
        #endif 
        #endif 
        ActuatorWtrPump.PumpStatusRequest = (PumpStatus_e)(recv - (char)'0');
        #endif
    }    
    ActuatorWtrPump.cyclic();
}
void Actu100ms(void)
{
    
}
void Actu10ms(void)
{

}
void Actu1ms(void)
{

}
void ActuSetValveOpen(void)
{
    ActuatorWtrPump.PumpStatusRequest = OPENING;
}
void ActuSetValveClosed(void)
{
    ActuatorWtrPump.PumpStatusRequest = CLOSING;
}