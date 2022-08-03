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
            //initialize RTC
            rtc.begin();
            //Get current time
            unsigned long epoch;
            uint8 numberOfTries = 0, maxTries = 6;

            do {
              epoch = WiFi.getTime();
              numberOfTries++;
            }
            while ((epoch == 0) && (numberOfTries < maxTries));
            
            if (numberOfTries == maxTries) {
                Serial.print("NTP unreachable!!");
                WateringControllerStateMachine = ERROR_WATERING;
            }
            else {
                Serial.print("Epoch received: ");
                Serial.println(epoch);
                rtc.setEpoch(epoch);
                Serial.println();
                WateringControllerStateMachine = RUNNING;
            }
            
        }
        else
        {
            //No way to know time
            //TODO, figure out best way to handle this
        }
        break;
    
    case RUNNING:
        printDate();
        printTime();
        Serial.println();    
        break;

    case ERROR_WATERING:
        Serial.println("Error");

    default:
        break;
    }
}

void WateringController_c::printTime()
{

  print2digits(rtc.getHours());

  Serial.print(":");

  print2digits(rtc.getMinutes());

  Serial.print(":");

  print2digits(rtc.getSeconds());

  Serial.println();
}

void WateringController_c::printDate()
{

  Serial.print(rtc.getDay());

  Serial.print("/");

  Serial.print(rtc.getMonth());

  Serial.print("/");

  Serial.print(rtc.getYear());

  Serial.print(" ");
}

void WateringController_c::print2digits(int number) {

  if (number < 10) {

    Serial.print("0");

  }

  Serial.print(number);
}