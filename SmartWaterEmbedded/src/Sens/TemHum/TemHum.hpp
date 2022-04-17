#ifndef TEMHUM_HPP
#define TEMHUM_HPP

#define TEMHUM_DEBUG 4

#include "Arduino.h"
#include "dht11\dht11.h"

class sensorTemHum_c
{
    private: /* Variables*/
        uint8_t digitalInput;
        float Humidity;
        float Temperature;
    public: /*variables*/

    private: /*methods*/

    public: /*Methods*/
    boolean init(uint8_t);
    void cyclic();
    float getTemperature();
    float getHumidity();
};

#endif