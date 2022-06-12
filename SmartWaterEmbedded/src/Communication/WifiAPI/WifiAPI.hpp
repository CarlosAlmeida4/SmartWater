#ifndef WIFIAPI_HPP
#define WIFIAPI_HPP

//#define WIFIAPI_DEBUG 9

#include "Arduino.h"
#include "Interface/Interface.hpp"
#include <WiFi101.h>
#include <SPI.h>

#define SSID_NAME "WaterPumpController"

class WifiAPI_c
{
    private: /*Variables*/
        int status = WL_IDLE_STATUS;
    public: /*Variables*/
        
    public: /*Methods*/
        void WifiAPIInit();
        void cyclic2s();
    private: /*Methods*/
#ifdef WIFIAPI_DEBUG
         void printWiFiStatus();
#endif
};

#endif 