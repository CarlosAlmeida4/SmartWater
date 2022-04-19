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
        debugPrint(SENSORS_DEBUG,"Failed to init Photoresistor");
    }
    if(SoilMoist.init(A5)!=true)
    {
        debugPrint(SENSORS_DEBUG,"Failed to init Soil moisture sensor");
    }
    if(TemHum.init(2)!=true)
    {
        debugPrint(SENSORS_DEBUG,"Failed to init DHT11 sensor");
    }
    if(WtrFlow.init(5)!=true)
    {
        debugPrint(SENSORS_DEBUG,"Failed to init WaterFlow sensor");
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