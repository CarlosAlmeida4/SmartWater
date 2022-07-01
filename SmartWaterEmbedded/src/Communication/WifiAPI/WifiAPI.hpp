#ifndef WIFIAPI_HPP
#define WIFIAPI_HPP

//#define WIFIAPI_DEBUG 9

#include "Arduino.h"
#include "Interface/Interface.hpp"
#include <WiFi101.h>
#include <SPI.h>

#include "secrets.h"

class WifiAPI_c
{
    private: /*Variables*/
        int status = WL_IDLE_STATUS;
    public: /*Variables*/
        
    public: /*Methods*/
        void WifiAPIInit();
        void cyclic2s();
    private: /*Methods*/
        void ChooseNetworks(int8_t *);
#ifdef WIFIAPI_DEBUG
        void printWiFiStatus();
#endif
};

#endif 