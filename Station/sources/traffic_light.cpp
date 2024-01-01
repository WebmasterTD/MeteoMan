#include "traffic_light.h"
#include <fmt/core.h>
#include <pigpio.h>

#define GREEN_MASK  (1 << 0)
#define YELLOW_MASK (1 << 1)
#define RED_MASK    (1 << 2)

ReturnCode traffic_light::init(const std::string& sSection)
{
    m_oConfReader = INIReader(CONFIG_FILENAME);
    m_nGreenLed = m_oConfReader.GetInteger(sSection, "green_led", -1);
    m_nYellowLed = m_oConfReader.GetInteger(sSection, "yellow_led", -1);
    m_nRedLed = m_oConfReader.GetInteger(sSection, "red_led", -1);
    if ((m_nGreenLed == -1) || (m_nYellowLed == -1) || (m_nRedLed == -1))
    {
        fmt::print(stderr, "Failed INI read\n");
        fmt::print(stderr, "m_nGreenLed:{}\n",m_nGreenLed);
        fmt::print(stderr, "m_nYellowLed:{}\n",m_nYellowLed);
        fmt::print(stderr, "m_nRedLed:{}\n",m_nRedLed);
        return ReturnCode::ERROR;
    }
    if (gpioInitialise() ==  PI_INIT_FAILED)
    {
        fmt::print(stderr, "Failed GPIOInit\n");
        return ReturnCode::ERROR;
    }
    if (gpioSetMode(m_nGreenLed, PI_OUTPUT) != 0)
    {
        fmt::print(stderr, "Failed SetMode Green\n");
        return ReturnCode::ERROR;
    }
    if (gpioSetMode(m_nYellowLed, PI_OUTPUT) != 0)
    {
        fmt::print(stderr, "Failed SetMode Yellow\n");
        return ReturnCode::ERROR;
    }
    if (gpioSetMode(m_nRedLed, PI_OUTPUT) != 0)
    {
        fmt::print(stderr, "Failed SetMode Red\n");
        return ReturnCode::ERROR;
    }
    set_state(state::XXX);
    return ReturnCode::OK;
}

ReturnCode traffic_light::set_state(const state light_state)
{
    bool green_state = light_state & GREEN_MASK;
    bool yellow_state = light_state & YELLOW_MASK;
    bool red_state = light_state & RED_MASK;
    
    gpioWrite(m_nGreenLed, green_state);
    gpioWrite(m_nYellowLed, yellow_state);
    gpioWrite(m_nRedLed, red_state);
    
    return ReturnCode::OK;
}

traffic_light::~traffic_light()
{
    gpioTerminate();
}