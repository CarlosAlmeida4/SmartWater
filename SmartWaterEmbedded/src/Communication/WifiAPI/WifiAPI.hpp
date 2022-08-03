#ifndef WIFIAPI_HPP
#define WIFIAPI_HPP

//#define WIFIAPI_DEBUG 9
#define RETRY_COUNTER 10

#include "Arduino.h"
#include "Interface/Interface.hpp"
#include <WiFi101.h>
#include <WiFiMDNSResponder.h>
#include <SPI.h>


typedef enum 
{
    NOT_CONNECTED,
    CONNECTED,
    STANDALONE,
    CONNECTING,
    ERROR_WIFI
}WifiAPIStateMachine_e;


class WifiAPI_c
{
    private: /*Variables*/
        int status = WL_IDLE_STATUS;
        boolean standAloneFlag = false;
        // Create a MDNS responder to listen and respond to MDNS name requests.
        WiFiMDNSResponder mdnsResponder;
    public: /*Variables*/
        WifiAPIStateMachine_e WifiAPIStatus;
    public: /*Methods*/
        void WifiAPIInit();
        void cyclic2s();
    private: /*Methods*/
        boolean ChooseNetworks(String *, uint8_t *);
        void InitConnection();
        void ScanNetworks(); /* Testing purposes */
        boolean SearchWifiNetwork();
        void ClientUpdate();
#ifdef WIFIAPI_DEBUG
        void printWiFiStatus();
#endif
};

#endif 