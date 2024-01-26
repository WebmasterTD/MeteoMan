#include "traffic_light.h"
#include "INIReader.h"
#include <fmt/core.h>

traffic_light::traffic_light():
m_oChip("gpiochip0")
{
}

ReturnCode traffic_light::init(const std::string& sSection)
{
    INIReader ConfReader(CONFIG_FILE_NAME);
    uint32_t GreenPin = ConfReader.GetInteger(sSection, "green_led", 0);
    uint32_t YellowPin = ConfReader.GetInteger(sSection, "yellow_led", 0);
    uint32_t RedPin = ConfReader.GetInteger(sSection, "red_led", 0);
    if ((GreenPin == 0) || (YellowPin == 0) || (RedPin == 0))
    {
        fmt::println(stderr, "Failed INI read");
        fmt::println(stderr, "Green Led PIN:{}",GreenPin);
        fmt::println(stderr, "Yellow Led PIN:{}",YellowPin);
        fmt::println(stderr, "Red Led PIN:{}",RedPin);
        return ReturnCode::ERROR;
    }
    m_oGreenLed = m_oChip.get_line(GreenPin);
    m_oYellowLed = m_oChip.get_line(YellowPin);
    m_oRedLed = m_oChip.get_line(RedPin);

    m_oGreenLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT, 0}, 0);  
    m_oYellowLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT, 0}, 0);  
    m_oRedLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT, 0}, 0);  

    return clear();
}

ReturnCode traffic_light::clear()
{
    m_oRedLed.set_value(false);
    m_oYellowLed.set_value(false);
    m_oGreenLed.set_value(false);

    return ReturnCode::OK;
}

ReturnCode traffic_light::Green(bool state)
{
    m_oGreenLed.set_value(state);
    return ReturnCode::OK;
}

ReturnCode traffic_light::Yellow(bool state)
{
    m_oYellowLed.set_value(state);
    return ReturnCode::OK;
}

ReturnCode traffic_light::Red(bool state)
{
    m_oRedLed.set_value(state);
    return ReturnCode::OK;
}

traffic_light::~traffic_light()
{
    if (m_oRedLed.is_requested())
        m_oRedLed.release();
    if (m_oYellowLed.is_requested())
        m_oYellowLed.release();
    if (m_oGreenLed.is_requested())
        m_oGreenLed.release();
}