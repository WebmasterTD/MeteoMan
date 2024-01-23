#include "bucket.h"
#include "INIReader.h"
#include <fmt/core.h>

bucket::bucket():
 m_bState(false),
 m_oChip("gpiochip0")
{
}

ReturnCode bucket::init(const std::string& sSection)
{
    INIReader ConfReader(CONFIG_FILENAME);
    uint32_t pin = ConfReader.GetInteger(sSection, "test_pin", -1);
    m_oLine = m_oChip.get_line(pin);
    m_oLine.request({"rain_bucket", gpiod::line_request::DIRECTION_INPUT, 0});
    return ReturnCode::OK;
}

ReturnCode bucket::read(float& fRain)
{
    bool val = m_oLine.get_value();
    if (val && val != m_bState)
    {
        fRain += 0.2 * val;
    }
    m_bState = val;
    return ReturnCode::OK;
}

bucket::~bucket()
{
    m_oLine.release();
}