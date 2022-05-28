#ifndef FIREBASEWIFI_HPP
#define FIREBASEWIFI_HPP

#define FIREBASEWIFI_DEBUG 9

#include "Arduino.h"
#include "Firebase_Arduino_WiFi101.h"
#include "WiFi101.h"

// Insert Firebase project API Key
#define API_KEY "AIzaSyATrqkuvcYy82iesSj1U2OdbruS5nh73Hk"
//Deprecated but still in usage here
#define DATABASE_SECRET "zMTDoOgjTMbHaABfTNDh8VHJwzSslIrxwlIikPgc"
// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://smartwater-48955-default-rtdb.europe-west1.firebasedatabase.app/"
// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "cesa4playstoretest@gmail.com"
#define USER_PASSWORD "SmartWater"
// WIFI
#define WIFI_SSID "TP-Link_AE60"
#define WIFI_PASSWORD "74231522"

class FirebaseWifi_c
{
    private:
        //Define Firebase data objects
        FirebaseData fbdo;
        
    private:
        wl_status_t initWifi();
    public:
        boolean init();
        void cyclic();
};

#endif 