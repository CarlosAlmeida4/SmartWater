#include "Sens.hpp"
#include "DebugFunction.hpp"
#include <string.h>

static sensorPhotoRes_c PhotoRes;
static sensorSoilMoist_c SoilMoist;
static sensorTemHum_c TemHum;
static sensorWtrFlow_c WtrFlow;

void SensorsInit(void)
{
    if(PhotoRes.init(A6)!=true)
    {
        #ifdef SENSORS_DEBUG
        debugPrint(SENSORS_DEBUG,"Failed to init Photoresistor");
        #endif
    }
    if(SoilMoist.init(A5)!=true)
    {
        #ifdef SENSORS_DEBUG
        debugPrint(SENSORS_DEBUG,"Failed to init Soil moisture sensor");
        #endif
    }
    if(TemHum.init(2)!=true)
    {
        #ifdef SENSORS_DEBUG
        debugPrint(SENSORS_DEBUG,"Failed to init DHT11 sensor");
        #endif
    }
    if(WtrFlow.init(5)!=true)
    {
        #ifdef SENSORS_DEBUG
        debugPrint(SENSORS_DEBUG,"Failed to init WaterFlow sensor");
        #endif
    }

}

void Sens2s(void)
{
    TemHum.cyclic();
}

void Sens1s(void)
{
    PhotoRes.cyclic();
    SoilMoist.cyclic();
}

void Sens100ms(void)
{
    WtrFlow.cyclic();
}

void Sens10ms(void)
{    
}

void Sens1ms(void)
{
}

SensorPhotoRes_e SensGetLightLevel(void)
{
    return PhotoRes.ActualLightLevel;
}

SimpleSoilStatus_e SensGetSimpleSoilStatus(void)
{
    return SoilMoist.getSimpleSoilStatus();
}

float SensGetAmbientHumidity(void)
{
    return TemHum.getHumidity();
}

float SensGetAmbientTemperature(void)
{
    return TemHum.getTemperature();
}