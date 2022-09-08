#include "WateringController.hpp"
#include "DebugFunction.hpp"
  // NOT_CONNECTED,
  // CONNECTED,
  // STANDALONE,
  // CONNECTING,
  // ERROR

/* Create an rtc object */
RTCZero rtc;
unsigned long epoch;

void StartWatering()
{
  WateringController2Actuator_SetValveOpen();
  rtc.setAlarmTime(0,40,10);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StartWatering);
}

void StopWatering()
{
  WateringController2Actuator_SetValveClosed();
  rtc.setAlarmTime(0,0,0);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StartWatering);
}

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
            uint8 numberOfTries = 0, maxTries = 6;

            do {
              epoch = WiFi.getTime();
              numberOfTries++;
            }
            while (((epoch > 0) || (numberOfTries > maxTries)) == false);
            
            if (numberOfTries == maxTries) {
                Serial.print("NTP unreachable!!");
                WateringControllerStateMachine = ERROR_WATERING;
            }
            else {
                Serial.print("Epoch received: ");
                Serial.println(epoch);
                rtc.setEpoch(epoch);
                Serial.println();
                //* Set initial alarm
                rtc.setAlarmTime(0,20,0);
                rtc.enableAlarm(rtc.MATCH_HHMMSS);
                rtc.attachInterrupt(StartWatering);
                rtc.standbyMode();
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
        rtc.standbyMode();    
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