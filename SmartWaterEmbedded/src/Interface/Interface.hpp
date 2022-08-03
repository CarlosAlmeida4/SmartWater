#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#define INTERFACE_DEBUG 10

#include "Arduino.h"
#include "Actuator/Actu.hpp"
#include "Sens/Sens.hpp"
#include "Communication/Communication.hpp"


/*             Wifi interfaces                */

/************Output****************************/
void WifiAPI2Actuator_SetValveOpen(void);
void WifiAPI2Actuator_SetValveClosed(void);
/************Input*****************************/
SensorPhotoRes_e WifiAPI2Sens_GetLightLevel(void);
//void setCalLightLevel(SensorPhotoRes_e,uint16_t);
SimpleSoilStatus_e WifiAPI2Sens_GetSimpleSoilStatus(void);
float WifiAPI2Sens_GetAmbientHumidity(void);
float WifiAPI2Sens_GetAmbientTemperature(void);

/*             Wifi interfaces                */
uint8_t WateringController2WifiAPI_GetWifiState(void);

/*         Watering Controller                */

/************Output****************************/
void WateringController2Actuator_SetValveOpen();
void WateringController2Actuator_SetValveClosed();
/************Input*****************************/
SensorPhotoRes_e WateringController2Sens_GetLightLevel(void);
SimpleSoilStatus_e WateringController2Sens_GetSimpleSoilStatus(void);
float WateringController2Sens_GetAmbientHumidity(void);
float WateringController2Sens_GetAmbientTemperature(void);

/*         Watering Controller                */

#endif 