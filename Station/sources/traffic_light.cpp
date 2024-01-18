#include "traffic_light.h"
#include "INIReader.h"
#include <fmt/core.h>

#define GREEN_MASK  (1 << 0)
#define YELLOW_MASK (1 << 1)
#define RED_MASK    (1 << 2)

traffic_light::traffic_light():
m_oChip("gpiochip0")
{
}

ReturnCode traffic_light::init(const std::string& sSection)
{
    INIReader ConfReader(CONFIG_FILENAME);
    uint32_t GreenPin = ConfReader.GetInteger(sSection, "green_led", -1);
    uint32_t YellowPin = ConfReader.GetInteger(sSection, "yellow_led", -1);
    uint32_t RedPin = ConfReader.GetInteger(sSection, "red_led", -1);
    if ((GreenPin == -1) || (YellowPin == -1) || (RedPin == -1))
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

    m_oGreenLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT}, 0);  
    m_oYellowLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT}, 0);  
    m_oRedLed.request({"traffic_light", gpiod::line_request::DIRECTION_OUTPUT}, 0);  

    set_state(state::XXX);
    return ReturnCode::OK;
}

ReturnCode traffic_light::set_state(const state light_state)
{
    m_oRedLed.set_value(light_state & RED_MASK);
    m_oYellowLed.set_value(light_state & YELLOW_MASK);
    m_oGreenLed.set_value(light_state & GREEN_MASK);

    return ReturnCode::OK;
}

traffic_light::~traffic_light()
{
}