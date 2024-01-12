#include "logic.h"
#include <unistd.h>
#include <string>

#include <fmt/core.h>
#include <chrono>

using namespace std::chrono;

ReturnCode Logic::init()
{
    // if(m_oTimer.init("TIMER") == ReturnCode::ERROR) return ReturnCode::ERROR;
    if (m_oSensor.init("MODBUS_RTU") == ReturnCode::ERROR)
        return ReturnCode::ERROR;
    if (m_oHttp.init("HTTP") == ReturnCode::ERROR)
        return ReturnCode::ERROR;
    if (m_oBucket.init("BUCKET") == ReturnCode::ERROR)
        return ReturnCode::ERROR;
    if (m_oTrafficLight.init("TRAFFIC_LIGHT") == ReturnCode::ERROR)
        return ReturnCode::ERROR;

    return ReturnCode::OK;
}

std::chrono::milliseconds get_time()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

void Logic::loop()
{
    // sleep(1);
    float humidity = 0.0;
    float temperature = 0.0;
    float rain = 0.0;

    milliseconds t0 = get_time();
    m_oSensor.read_humid(humidity);
    milliseconds t1 = get_time();
    m_oSensor.read_temp(temperature);
    milliseconds t2 = get_time();
    m_oBucket.read(rain);
    milliseconds t3 = get_time();

    fmt::print("Measured Data: {} | {} | {}\n", std::to_string(humidity), std::to_string(temperature), std::to_string(rain));

    // m_oTrafficLight.set_state(traffic_light::XXG);
    
    m_oTrafficLight.set_state(traffic_light::XXX);
    // sleep(1);

    // send data over http with curl
    // m_oHttp.send_data();

    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     m_oTrafficLight.set_state((traffic_light::states)i);
    //     sleep(1);
    // }

    // read_bucket;
    // if()
    // {

    // }
    // if(timer_1h_expired)
    // {
    //     send_http;
    // }

    // fmt::print("humid:{} temp:{} bucket:{}\n", (t1-t0).count(), (t2-t1).count(), (t3-t2).count() );
}