#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "cwt_modbus.h"
#include "http_comm.h"
#include "bucket.h"
#include "traffic_light.h"
#include "tick.h"
#include "ring_buffer.h"

class Logic
{
public:
    ReturnCode init();
    void loop();

private:
    // MODBUS
    cwt_modbus m_oSensor;
    tick m_oSensorTick;
    ring_buffer<float, 100> m_oTempData;
    ring_buffer<float, 100> m_oHumidData;

    // RAIN
    bucket m_oBucket;
    float m_oRainData;

    // TRAFFIC LIGHT
    traffic_light m_oTrafficLight;

    // HTTP
    http_comm m_oHttp;
    tick m_oHttpTick;
};

#endif //__LOGIC_H__