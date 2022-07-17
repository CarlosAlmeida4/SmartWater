#include "WateringController.hpp"
#include "DebugFunction.hpp"
  // NOT_CONNECTED,
  // CONNECTED,
  // STANDALONE,
  // CONNECTING,
  // ERROR


void WateringController_c::cyclic()
{
    
    switch (WateringControllerStateMachine)
    {
    case INIT:
        // Check if connected to network
        if(CONNECTED == WateringController2WifiAPI_GetWifiState())
        {
            //Get current time
            
        }
        else
        {
            //No way to know time
            //TODO, figure out best way to handle this
        }
        break;
    
    default:
        break;
    }
}