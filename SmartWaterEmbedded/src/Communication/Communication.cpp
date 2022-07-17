#include "Communication.hpp"
#include "DebugFunction.hpp"
#include "WifiAPI/WifiAPI.hpp"

WifiAPI_c WifiAPI;

void CommunicationInit()
{   
    WifiAPI.WifiAPIInit();
    //FirebaseWifi.init();
}

void Communication2s()
{
    //FirebaseWifi.cyclic();
    WifiAPI.cyclic2s();
}