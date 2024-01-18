#include "logic.h"
#include <fmt/core.h>

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
    state = 0;
    return ReturnCode::OK;
}

void Logic::loop()
{
    // m_oBucket.read(m_oData.rain);
    m_oSensor.read_all(m_oData.humidity, m_oData.temperature);
    

    if (m_oHttp.Timer.expired())
    {
        m_oData.timestamp = time(nullptr);
        m_oHttp.send_data(m_oData);
    }

    // if (state++ % 2)
    // {
    //     m_oTrafficLight.set_state(traffic_light::XXX);
    //     state = 0;
    // }
    // else
    // {
    //     m_oTrafficLight.set_state(traffic_light::RXX);
    // }
}