#include "Communication.hpp"
#include "DebugFunction.hpp"


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

uint8_t CommunicationGetWifiState()
{
    return WifiAPI.WifiAPIStatus;
}

AlarmTime CommunicationGetAlarmTime()
{
    return WifiAPI.wifiAlarmTime;
}