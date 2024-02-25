#include "logic.h"
#include "INIReader.h"
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

    INIReader ConfReader(CONFIG_FILE_NAME);

    struct timeval sensor_period = {};
    struct timeval http_period = {};
    sensor_period.tv_sec = ConfReader.GetInteger("LOGIC", "sensor_s", 5);
    http_period.tv_sec = ConfReader.GetInteger("LOGIC", "http_s", 300);

    m_oRainData = 0.0;
    m_oSensorTick.init(sensor_period, false);
    m_oHttpTick.init(http_period, false);
    return ReturnCode::OK;
}

void Logic::loop()
{
    m_oTrafficLight.clear();

    m_oBucket.read(m_oRainData);

    if (m_oSensorTick.expired())
    {
        float temp = 0.0;
        float humid = 0.0;
        m_oSensor.read_all(humid, temp);
        m_oTempData.add_value(temp);
        m_oHumidData.add_value(humid);
        m_oTrafficLight.Yellow(true);
    }
    
    if (m_oHttpTick.expired())
    {
        http_data data = {};
        data.timestamp = time(nullptr);
        data.temperature = m_oTempData.average();
        data.humidity = m_oHumidData.average();
        data.rain = m_oRainData;
        m_oHttp.send_data(data);
        m_oTrafficLight.Green(true);
        m_oRainData = 0.0;
    }
}