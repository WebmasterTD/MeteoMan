#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "cwt_modbus.h"
#include "http_comm.h"
#include "bucket.h"
#include "traffic_light.h"
#include "timer.h"
#include "tick.h"

#include <future>

#include <chrono>

#define TIMING

#ifdef TIMING

#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER                                        \
    do                                                     \
    {                                                      \
        start = std::chrono::high_resolution_clock::now(); \
    } while (0)
#define STOP_TIMER(name)                                                                                                                                              \
    do                                                                                                                                                                \
    {                                                                                                                                                                 \
        fmt::print("RUNTIME of {}: {}ms \n", name, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count()); \
    } while (0)
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif

#define INIT_OK(x)                                             \
    {                                                          \
        int _ret = x;                                          \
        if (_ret < 0)                                          \
        {                                                      \
            fmt::print(stderr, "err: {}\n", _ret) return _ret; \
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
    // tick m_oModbusTimer;

    bucket m_oBucket;
    traffic_light m_oTrafficLight;
    
    // HTTP
    http_comm m_oHttp;

    std::future<ReturnCode> m_oHttpReply;
};

#endif //__LOGIC_H__