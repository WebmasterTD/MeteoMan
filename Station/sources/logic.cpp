#include "logic.h"
#include <unistd.h>
#include <string>

#include <fmt/core.h>
#include <chrono>

using namespace std::chrono;

ReturnCode Logic::init()
{
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

void Logic::loop()
{
    // INIT_TIMER;
    float humidity = 0.0;
    float temperature = 0.0;
    float rain = 0.0;

    m_oSensor.read_all(humidity, temperature);

    m_oBucket.read(rain);

    // fmt::print("Measured Data: {} | {} | {}\n", std::to_string(humidity), std::to_string(temperature), std::to_string(rain));

    switch (m_oHttp.State)
    {
        case http_comm::WAIT_FOR_TIMER:
            if (!m_oHttp.Timer.expired())
            {
                break;
            }
            m_oHttp.State = http_comm::SEND_HTTP;
            [[fallthrough]];
        case http_comm::SEND_HTTP:
        {
            http_data data =
                {
                    .temperature = temperature,
                    .humidity = humidity,
                    .rain = rain};
            data.timestamp = time(nullptr);
            m_oHttpReply = std::async(&http_comm::send_data, &m_oHttp, data);
            m_oHttp.State = http_comm::WAIT_FOR_HTTP;
            break;
        }
        case http_comm::WAIT_FOR_HTTP:
            if (!m_oHttpReply.valid())
            {
                break;
            }
            m_oHttp.State = http_comm::GET_REPLY;
            [[fallthrough]];
        case http_comm::GET_REPLY:
            if (m_oHttpReply.get() != ReturnCode::OK)
            {
                fmt::print("ERROR: HTTP send failed!\n");
                m_oHttp.State = http_comm::WAIT_FOR_TIMER;
                // for retry:
                // m_oHttp.State = http_comm::SEND_HTTP;
            }
            else
            {
                m_oHttp.State = http_comm::WAIT_FOR_TIMER;
            }
            break;
    }
    // STOP_TIMER("main_loop");
}