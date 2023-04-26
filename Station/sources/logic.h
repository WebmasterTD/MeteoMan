#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "cwt_modbus.h"
#include "http_comm.h"
#include "bucket.h"
#include "traffic_light.h"
#include "timer.h"


#define INIT_OK(x)      \
    {                    \
        int _ret  = x;   \
        if (_ret < 0)    \
        {                \
            fmt::print("err: {}\n", _ret) \
            return _ret; \
        }                \
    }                    \

class Logic
{
public:
    ReturnCode init();
    void loop();
    void error();
private:
    cwt_modbus      m_oSensor;
    http_comm       m_oHttp;
    bucket          m_oBucket;
    traffic_light   m_oTrafficLight;
    timer           m_oTimer; 
};

#endif //__LOGIC_H__ 