#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "cwt_modbus.h"
#include "http_comm.h"
#include "bucket.h"
#include "traffic_light.h"
#include "timer.h"
#include "tick.h"

#define INIT_OK(x)                                             \
    {                                                          \
        int _ret = x;                                          \
        if (_ret < 0)                                          \
        {                                                      \
            fmt::println(stderr, "err: {}", _ret) return _ret; \
        }                                                      \
    }

class Logic
{
public:
    ReturnCode init();
    void loop();

private:
    // MODBUS
    cwt_modbus m_oSensor;

    bucket m_oBucket;
    
    traffic_light m_oTrafficLight;
    int state;

    // HTTP
    http_comm m_oHttp;
    http_data m_oData;
    std::future<ReturnCode> m_oHttpReply;

};

#endif //__LOGIC_H__