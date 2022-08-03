#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#define COMMUNICATION_DEBUG 8

#include "Arduino.h"
#include "WifiAPI/WifiAPI.hpp"

void CommunicationInit();
void Communication2s();
uint8_t CommunicationGetWifiState();

#endif 