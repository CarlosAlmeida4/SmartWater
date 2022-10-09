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

static WateringControllerAlarm_e AlarmState = NO_INIT;
void StopWatering();
void StartWatering()
{
  WateringController2Actuator_SetValveOpen();
  rtc.setAlarmTime(0,30,0);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StopWatering);
}

void StopWatering()
{
  WateringController2Actuator_SetValveClosed();
  rtc.setAlarmTime(0,0,0);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StartWatering);
}

WateringControllerAlarm_e WateringAlarmCallback(WateringControllerAlarm_e changeState)
{
  AlarmState = changeState;
  return AlarmState;
}

WateringControllerAlarm_e WateringAlarmCallback(void)
{
  return AlarmState;
}

void WateringController_c::setAlarmTime()
{
  rtc.setAlarmTime(alarmTime.StartHour,alarmTime.StartMinute,alarmTime.StartSecond);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StartWatering);
  rtc.standbyMode();
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
            uint8 numberOfTries = 0, maxTries = UINT8_MAX;

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
                /*rtc.setAlarmTime(23,47,0);
                rtc.enableAlarm(rtc.MATCH_HHMMSS);
                rtc.attachInterrupt(StartWatering);
                rtc.standbyMode();*/
                WateringControllerStateMachine = RUNNING;
                (void)WateringAlarmCallback(NO_ALARM);
            }
            
        }
        else
        {
            //No way to know time
            //TODO, figure out best way to handle this
        }
        break;
    
    case RUNNING:
        //printDate();
        //printTime();
        //Serial.println(); 
        //rtc.standbyMode();
        if(SET_ALARM == WateringAlarmCallback())
        {
          AlarmTime receivedAlarm;
          WateringController2WifiAPI_GetAlarmTime(&receivedAlarm);
          alarmTime = receivedAlarm;
        }
        RunningAction();  
        break;

    case ERROR_WATERING:
        Serial.println("Error");

    default:
        break;
    }
}

void WateringController_c::RunningAction()
{

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