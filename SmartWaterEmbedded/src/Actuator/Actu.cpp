#include "Actu.hpp"
#include "DebugFunction.hpp"

static ActuatorWtrPump_c ActuatorWtrPump; 

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
        char recv; 
        Serial.readBytes(&recv,1);
        Serial.print("Received char: ");
        Serial.println(recv);
        ActuatorWtrPump.PumpStatusRequest = (PumpStatus_e)(recv - (char)'0');
        Serial.print("PumpStatusRequest: ");
        Serial.println(ActuatorWtrPump.PumpStatusRequest);
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
