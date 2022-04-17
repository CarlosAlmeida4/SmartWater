#include "TemHum.hpp"
#include "DebugFunction.hpp"

dht11 DHT;
/**
 * @brief Initialization of the temperature adn hum sensor
 * 
 * @param InputPin pin used to communicate with the sensor
 * @return boolean true if initialized ok false if not
 */
boolean sensorTemHum_c::init(uint8_t InputPin)
{
    digitalInput = InputPin;
    /* TODO: Implement logic to check sensor (short to gnd short to VCC) */
    return true;
}
/**
 * @brief Cyclic upates temperature and humidity
 * nees to be slower than 1 second task
 *
 */
void sensorTemHum_c::cyclic()
{
    int chk;
#ifdef DEBUG_ENABLED
    Serial.print("DHT11, \t");
#endif
    chk = DHT.read(digitalInput); // READ DATA
    /* TODO Implement error checking */
    switch (chk)
    {
    case DHTLIB_OK:
#ifdef DEBUG_ENABLED
        Serial.print("OK,\t");
#endif
        break;
    case DHTLIB_ERROR_CHECKSUM:
#ifdef DEBUG_ENABLED
        Serial.print("Checksum error,\t");
#endif
        break;
    case DHTLIB_ERROR_TIMEOUT:
#ifdef DEBUG_ENABLED
        Serial.print("Time out error,\t");
#endif
        break;
    default:
#ifdef DEBUG_ENABLED
        Serial.print("Unknown error,\t");
#endif
        break;
    }

    Humidity = DHT.humidity;
    Temperature = DHT.temperature;

#ifdef DEBUG_ENABLED
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.println(DHT.temperature, 1);
#endif
}
/**
 * @brief Return the humidity in RH
 * 
 * @return float 
 */
float sensorTemHum_c::getHumidity()
{
    return Humidity;
}
/**
 * @brief Returns the temp in C
 * 
 * @return float 
 */
float sensorTemHum_c::getTemperature()
{
    return Temperature;
}