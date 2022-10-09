#include "Interface.hpp"
#include "DebugFunction.hpp"
#include "WateringController/WateringController.hpp"


/*             Wifi interfaces                */

void WifiAPI2Actuator_SetValveOpen()
{
    ActuSetValveOpen();
}

void WifiAPI2Actuator_SetValveClosed()
{
    ActuSetValveClosed();
}

SensorPhotoRes_e WifiAPI2Sens_GetLightLevel(void)
{
    return SensGetLightLevel();
}

SimpleSoilStatus_e WifiAPI2Sens_GetSimpleSoilStatus(void)
{
    return SensGetSimpleSoilStatus();    
}

float WifiAPI2Sens_GetAmbientHumidity(void)
{
    return SensGetAmbientHumidity();
}

float WifiAPI2Sens_GetAmbientTemperature(void)
{
    return SensGetAmbientTemperature();
}

void WifiApi2WateringController_TriggerAlarm()
{
    (void)WateringAlarmCallback(SET_ALARM);
}

/*         Watering Controller                */

void WateringController2WifiAPI_GetAlarmTime(AlarmTime* currentAlarm)
{
    *currentAlarm = CommunicationGetAlarmTime();
}

uint8_t WateringController2WifiAPI_GetWifiState()
{
    return CommunicationGetWifiState();
}

void WateringController2Actuator_SetValveOpen()
{
    ActuSetValveOpen();
}

void WateringController2Actuator_SetValveClosed()
{
    ActuSetValveClosed();
}

SensorPhotoRes_e WateringController2Sens_GetLightLevel(void)
{
    return SensGetLightLevel();
}

SimpleSoilStatus_e WateringController2Sens_GetSimpleSoilStatus(void)
{
    return SensGetSimpleSoilStatus();    
}

float WateringController2Sens_GetAmbientHumidity(void)
{
    return SensGetAmbientHumidity();
}

float WateringController2Sens_GetAmbientTemperature(void)
{
    return SensGetAmbientTemperature();
}

/*         Watering Controller                */