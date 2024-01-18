#include "bucket.h"
#include "INIReader.h"
#include <fmt/core.h>

bucket::bucket():
m_oChip("gpiochip0")
{
}

ReturnCode bucket::init(const std::string& sSection)
{
    INIReader ConfReader(CONFIG_FILENAME);
    uint32_t pin = ConfReader.GetInteger(sSection, "test_pin", -1);
    m_oLine = m_oChip.get_line(pin);
    m_oLine.request({"rain_bucket", gpiod::line_request::DIRECTION_INPUT});
    return ReturnCode::OK;
}

ReturnCode bucket::read(float& fRain)
{
    int val = m_oLine.get_value();
    return ReturnCode::OK;
}

bucket::~bucket()
{
    m_oLine.release();
}