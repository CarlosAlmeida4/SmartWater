#include "WifiAPI.hpp"
#include "DebugFunction.hpp"

WiFiServer server(80);

void WifiAPI_c::WifiAPIInit()
{
    status = WiFi.beginAP(SSID_NAME);
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
    // start the web server on port 80
    server.begin();
    #ifdef WIFIAPI_DEBUG
    printWiFiStatus();
    #endif
}

void WifiAPI_c::cyclic2s()
{
    
    // compare the previous status to the current status
    if (status != WiFi.status())
    {
        // it has changed update the variable
        status = WiFi.status();
        if (status == WL_AP_CONNECTED)
        {
            #ifdef WIFIAPI_DEBUG
            // a device has connected to the AP
            Serial.println("Device connected to AP");
            #endif
        }
        else
        {
            #ifdef WIFIAPI_DEBUG
            // a device has disconnected from the AP, and we are back in listening mode
            Serial.println("Device disconnected from AP");
            #endif
        }
    }

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