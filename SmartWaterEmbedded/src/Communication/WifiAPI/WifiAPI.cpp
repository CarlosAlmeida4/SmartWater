#include "WifiAPI.hpp"
#include "DebugFunction.hpp"

#include "secrets.h"

WiFiServer server(80);

void WifiAPI_c::WifiAPIInit()
{
    WifiAPIStatus = NOT_CONNECTED;
    #ifdef WIFIAPI_DEBUG
    printWiFiStatus();
    #endif
}

boolean WifiAPI_c::ChooseNetworks(String * ACorrect_ssid, uint8_t * objectId)
{   
    boolean found_network = false;
    String Correct_ssid;
    // scan for nearby networks:
    #ifdef WIFIAPI_DEBUG
    Serial.println("** Scan Networks **");
    #endif
    int8_t numSsid= WiFi.scanNetworks();
    if (numSsid == -1)
    {
      Serial.println("Couldn't get a wifi connection");
    }

    // print the list of networks seen:
    #ifdef WIFIAPI_DEBUG
    Serial.print("number of available networks:");
    Serial.println(numSsid);
    #endif

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
        #ifdef WIFIAPI_DEBUG
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.print("\tSignal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.println("\tEncryption: ");
        Serial.flush();
        #endif

        for(int i = 0; i < SSID_LIST_SIZE; i++)
        {
            #ifdef WIFIAPI_DEBUG
            Serial.print("Iteration: ");
            Serial.println(i);
            Serial.print("Found Network: ");
            Serial.println(WiFi.SSID(thisNet));
            Serial.print("Comparision Network: ");
            Serial.println(SsidList[i]);
            #endif
            if(strcmp(WiFi.SSID(thisNet),SsidList[i]) == 0)
            {
                Correct_ssid = WiFi.SSID(thisNet);
                #ifdef WIFIAPI_DEBUG
                Serial.println("I will try to connect to this network: ");
                Serial.println(Correct_ssid);
                #endif
                *objectId = (uint8_t)thisNet;
                *ACorrect_ssid = Correct_ssid;
                found_network = true;
            }
        }
    }

    return found_network;
}

void WifiAPI_c::InitConnection()
{
    String CurrentSsid;
    uint8_t SsidObjectId = 255;

    static uint8_t retryCounter = 0;

    if(ChooseNetworks(&CurrentSsid, &SsidObjectId))
    {
        // A know SSID exists
        #ifdef WIFIAPI_DEBUG
        Serial.print("The current Ssid is: ");
        Serial.println(CurrentSsid.c_str());
        #endif
        standAloneFlag = false;
        while(status!= WL_CONNECTED)
        {
            status = WiFi.begin(SsidList[SsidObjectId],SsidPassWord[SsidObjectId]);
            Serial.print("Trying to connect to: ");
            Serial.println(SsidList[SsidObjectId]);
            Serial.print("With Password: ");
            Serial.println(SsidPassWord[SsidObjectId]);
            retryCounter++;
        }

    }
    else
    {
        status = WiFi.beginAP(SSID_STANDALONE);
        standAloneFlag = true;
        if (status != WL_AP_LISTENING)
        {
            // don't continue
            while (true)
            {
                #ifdef WIFIAPI_DEBUG
                Serial.println("Creating access point failed");
                #endif
            }
        }
    }

    server.begin();

    // Setup the MDNS responder to listen to the configured name.
    // NOTE: You _must_ call this _after_ connecting to the WiFi network and
    // being assigned an IP address.
    if (!mdnsResponder.begin(mdnsName)) {
      Serial.println("Failed to start MDNS responder!");
    };

    Serial.print("Server listening at http://");
    Serial.print(mdnsName);
    Serial.println(".local/");
}

boolean WifiAPI_c::SearchWifiNetwork()
{
    String CurrentSsid;
    uint8_t SsidObjectId = 255;

    if(ChooseNetworks(&CurrentSsid, &SsidObjectId))
    {
        // A know SSID exists
        #ifdef WIFIAPI_DEBUG
        Serial.print("The current Ssid is: ");
        Serial.println(CurrentSsid.c_str());
        #endif
        standAloneFlag = false;
        while(status!= WL_CONNECTED)
        {
            status = WiFi.begin(SsidList[SsidObjectId],SsidPassWord[SsidObjectId]);
            Serial.print("Trying to connect to: ");
            Serial.println(SsidList[SsidObjectId]);
            Serial.print("With Password: ");
            Serial.println(SsidPassWord[SsidObjectId]);
        }
    }
}

void WifiAPI_c::cyclic2s()
{
    Serial.print("Current WifiAPI status: ");
    Serial.println(WifiAPIStatus);
    Serial.print("Current Wifi status: ");
    Serial.println(status);

    switch (WifiAPIStatus)
    {
        case NOT_CONNECTED: /*Search for a connection or create AP */
            InitConnection();
            WifiAPIStatus = CONNECTING;
            break;
        case STANDALONE:
            // Check if a known network can be connected
            // TODO check how to search networks when AP is already started
            //SearchWifiNetwork();
            mdnsResponder.poll();
            ClientUpdate();
            break;
        case CONNECTED:
            mdnsResponder.poll();
            ClientUpdate();
        default:
            break;
    }
    //if it has changed update the variable
    status = WiFi.status();
    switch (status)
    {
        case WL_AP_CONNECTED:
        case WL_AP_LISTENING:
            WifiAPIStatus = STANDALONE;
            break;
        case WL_CONNECTED:
            WifiAPIStatus = CONNECTED;
            break;
        case WL_CONNECTION_LOST:
            WifiAPIStatus = NOT_CONNECTED;
        default:
            break;
    }
    


}

void WifiAPI_c::ScanNetworks()
{
    Serial.println("** Scan Networks **");
    int8_t numSsid= WiFi.scanNetworks();
    if (numSsid == -1)
    {
      Serial.println("Couldn't get a wifi connection");
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.print("\tSignal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.print("\tEncryption: ");
        Serial.flush();
        
        for(int i = 0; i < SSID_LIST_SIZE; i++)
        {
            if(strcmp(WiFi.SSID(thisNet),SsidList[i]) == 0)
            {
                Serial.println("I will try to connect to this network ");
            }
        }
    }
}

void WifiAPI_c::ClientUpdate()
{
    WiFiClient client = server.available(); // listen for incoming clients
    if (client)
    {   
        #ifdef WIFIAPI_DEBUG          // if you get a client,
        Serial.println("new client"); // print a message out the serial port
        #endif
        String currentLine = "";      // make a String to hold incoming data from the client
        while (client.connected())
        { // loop while the client's connected
            if (client.available())
            {                           // if there's bytes to read from the client,
                char c = client.read(); // read a byte, then
                #ifdef WIFIAPI_DEBUG   
                Serial.write(c);        // print it out the serial monitor
                #endif
                if (c == '\n')
                { // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0)
                    {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        // the content of the HTTP response follows the header:
                        client.print("Click <a href=\"/H\">here</a> to open the valve<br>");
                        client.print("Click <a href=\"/L\">here</a> to close the valve<br>");
                        // The HTTP response ends with another blank line:
                        client.println();
                        client.print("Light level: ");
                        client.print(WifiAPI2Sens_GetLightLevel());
                        client.println("<br>");
                        client.print("Soil Moisture: ");
                        client.print(WifiAPI2Sens_GetSimpleSoilStatus());
                        client.println("<br>");
                        client.print("Ambient Humidity: ");
                        client.print(WifiAPI2Sens_GetAmbientHumidity());
                        client.println("<br>");
                        client.print("Ambient Temperature: ");
                        client.print(WifiAPI2Sens_GetAmbientTemperature());
                        client.println("<br>");
                        client.println();
                        // break out of the while loop:
                        break;
                    }
                    else
                    { // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {                     // if you got anything else but a carriage return character,
                    currentLine += c; // add it to the end of the currentLine
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /H"))
                {
                    WifiAPI2Actuator_SetValveOpen();
                }
                if (currentLine.endsWith("GET /L"))
                {
                    WifiAPI2Actuator_SetValveClosed();
                }
            }
        }
        // close the connection:
        client.stop();
        #ifdef WIFIAPI_DEBUG  
        Serial.println("client disconnected");
        #endif
    }
}

#ifdef WIFIAPI_DEBUG
void WifiAPI_c::printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print where to go in a browser:
    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(ip);
}
#endif