#include "logic.h"
#include <unistd.h>
//#include <logger.hpp>
#include <string>

#include <fmt/core.h>

ReturnCode Logic::init()
{
    if(m_oTimer.init("TIMER") == ReturnCode::ERROR) return ReturnCode::ERROR;
    if(m_oSensor.init("MODBUS_RTU") == ReturnCode::ERROR) return ReturnCode::ERROR;
    if(m_oHttp.init("HTTP") == ReturnCode::ERROR) return ReturnCode::ERROR;
    if(m_oBucket.init("BUCKET") == ReturnCode::ERROR) return ReturnCode::ERROR;
    if(m_oTrafficLight.init("TRAFFIC_LIGHT") == ReturnCode::ERROR) return ReturnCode::ERROR;
    // LOGGER.log(LogLevel::INFO, "Logic initialized");
    return ReturnCode::OK;
}

void Logic::loop()
{
    float humidity = 0.0;
    float temperature = 0.0;
    float rain = 0.0;

    while(true) // m_bRun
    {
        // m_oTimer.wait();

        // TODO: error checking + escape condition eg. retries
        m_oSensor.read_humid(humidity);
        m_oSensor.read_temp(temperature);
        m_oBucket.read(rain);
        
        // construct msg
        std::string log = "Measured Data: " + std::to_string(humidity) + " | " + std::to_string(temperature) + " | " + std::to_string(rain);
        
        // LOGGER.log(LogLevel::INFO, log);

        fmt::print("Hello, world!\n");

        m_oTrafficLight.set_state(traffic_light::XXG);
        sleep(1);
        m_oTrafficLight.set_state(traffic_light::XXX);
        sleep(1);
        // send data over http with curl
        // m_oHttp.send_data();

        // for (uint8_t i = 0; i < 8; i++)
        // {
        //     m_oTrafficLight.set_state((traffic_light::states)i);
        //     sleep(1);
        // }
        // Logger::log(LogLevel::DEBUG, "test log");
        
    }
}

void Logic::error()
{
}