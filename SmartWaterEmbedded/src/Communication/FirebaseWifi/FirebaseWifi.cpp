#include "FirebaseWifi.hpp"
#include "DebugFunction.hpp"

boolean FirebaseWifi_c::init()
{
#ifdef FIREBASEWIFI_DEBUG
    Serial.print("Connecting to Wi-Fi");
#endif

#ifdef FIREBASEWIFI_DEBUG
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
#endif
    initWifi();

    // Provide the autntication data
    Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
    Firebase.reconnectWiFi(true);
    
}

wl_status_t FirebaseWifi_c::initWifi()
{
    wl_status_t status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED)
    {
        status =(wl_status_t) WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print(".");
        delay(100);
    }
}

void FirebaseWifi_c::cyclic()
{
#ifdef FIREBASEWIFI_DEBUG
    Serial.println(fbdo.errorReason());
    Serial.println(fbdo.httpCode());
    Serial.println(fbdo.httpConnected());
#endif

}