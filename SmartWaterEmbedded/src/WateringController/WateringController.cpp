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
static AlarmTime lcl_alarmTime;
static WateringControllerAlarm_e AlarmState = NO_INIT;
void StopWatering();

void StartWatering()
{
  #ifdef WATERINGCONTROLLER_DEBUG
  Serial.println("The Watering is going to start: ");
  Serial.print("Hour: ");
  Serial.println(rtc.getHours());
  Serial.print("Minute: ");
  Serial.println(rtc.getMinutes());
  #endif
  WateringController2Actuator_SetValveOpen();
  rtc.setAlarmTime(rtc.getHours(),(rtc.getMinutes()+lcl_alarmTime.duration),0);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StopWatering);
}

void StopWatering()
{
  #ifdef WATERINGCONTROLLER_DEBUG
  Serial.println("The Watering is going to end: ");
  Serial.print("Hour: ");
  Serial.println(rtc.getHours());
  Serial.print("Minute: ");
  Serial.println(rtc.getMinutes());
  #endif
  WateringController2Actuator_SetValveClosed();
  rtc.setAlarmTime(lcl_alarmTime.StartHour,lcl_alarmTime.StartMinute,lcl_alarmTime.StartSecond);
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

/*void WateringController_c::setAlarmTime()
{
  rtc.setAlarmTime(alarmTime.StartHour,alarmTime.StartMinute,alarmTime.StartSecond);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(StartWatering);
}*/
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
                /* TODO: Fix this patch, safeguard against epoch = 0*/
                if(0 != epoch)
                {
                  WateringControllerStateMachine = RUNNING;
                }
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
  //printDate();
  //printTime();
  //Serial.println(); 
  //rtc.standbyMode();
  #ifdef WATERINGCONTROLLER_DEBUG
  Serial.print(" AlarmCallback status: ");
  Serial.println(WateringAlarmCallback());
  #endif 
  if(SET_ALARM == WateringAlarmCallback())
  {
    // Get alarm from wifi
    AlarmTime receivedAlarm;
    WateringController2WifiAPI_GetAlarmTime(&receivedAlarm);
    alarmTime = receivedAlarm;
    #ifdef WATERINGCONTROLLER_DEBUG
    Serial.println("The alarmTime struct is: ");
    Serial.print("Hour: ");
    Serial.println(alarmTime.StartHour);
    Serial.print("Minute: ");
    Serial.println(alarmTime.StartMinute);
    Serial.print("Duration: ");
    Serial.println(alarmTime.duration);
    #endif
    lcl_alarmTime = alarmTime;
    //check if inside the watering time window
    if(rtc.getHours() == alarmTime.StartHour)
    {
      #ifdef WATERINGCONTROLLER_DEBUG
      Serial.println("The Current time is: ");
      Serial.print("Hour: ");
      Serial.println(rtc.getHours());
      Serial.print("Minute: ");
      Serial.println(rtc.getMinutes());
      #endif
      //Setup routine
      rtc.setAlarmTime(alarmTime.StartHour,alarmTime.StartMinute,alarmTime.StartSecond);
      rtc.enableAlarm(rtc.MATCH_HHMMSS);
      rtc.attachInterrupt(StartWatering);
    }
    else
    { 
      #ifdef WATERINGCONTROLLER_DEBUG
      Serial.println("The Current time is: ");
      Serial.print("Hour: ");
      Serial.println(rtc.getHours());
      Serial.print("Minute: ");
      Serial.println(rtc.getMinutes());
      #endif
      //Setup routine
      rtc.setAlarmTime(alarmTime.StartHour,alarmTime.StartMinute,alarmTime.StartSecond);
      rtc.enableAlarm(rtc.MATCH_HHMMSS);
      rtc.attachInterrupt(StartWatering);
    }
    //Change alarm status
    (void)WateringAlarmCallback((WateringControllerAlarm_e)ARMED);
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