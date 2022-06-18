#include "WateringController.hpp"
#include "DebugFunction.hpp"


void WateringController_c::cyclic()
{
    
    switch (WateringController2Sens_GetLightLevel())
    {
    case DAWN_DUSK:
        if(SOIL_DRY == WateringController2Sens_GetSimpleSoilStatus())
        {
            if(WateringController2Sens_GetAmbientHumidity()<=80)
            {
                debugPrint(WATERINGCONTROLLER_DEBUG,"Opened valve because Dawn_dusk");
                WateringController2Actuator_SetValveOpen();
            }
            
        }
        else
        {
            WateringController2Actuator_SetValveClosed();
            debugPrint(WATERINGCONTROLLER_DEBUG,"Closed valve because Dawn_dusk and Soil is not dry");
        }
        break;
    case CLOUDY:
        if(SOIL_DRY == WateringController2Sens_GetSimpleSoilStatus())
        {
            if(WateringController2Sens_GetAmbientHumidity()<=80 || WateringController2Sens_GetAmbientTemperature()>=26)
            {
                debugPrint(WATERINGCONTROLLER_DEBUG,"Opened valve because Cloudy");
                WateringController2Actuator_SetValveOpen();
            }
            
        }
        else
        {
            debugPrint(WATERINGCONTROLLER_DEBUG,"Closed valve because Cloudy and Soil is not dry");
            WateringController2Actuator_SetValveClosed();
        }
        break;
    default:
        debugPrint(WATERINGCONTROLLER_DEBUG,"Closed valve because not Cloudy and not Dawn_dusk and Soil is not dry");
        WateringController2Actuator_SetValveClosed();
        break;
    }
    
}