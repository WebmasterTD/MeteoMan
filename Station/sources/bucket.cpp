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
    INIReader ConfReader(CONFIG_FILE_NAME);
    uint32_t pin = static_cast<uint32_t>(ConfReader.GetInteger(sSection, "test_pin", 0));
    m_oLine = m_oChip.get_line(pin);
    m_oLine.request({"rain_bucket", gpiod::line_request::DIRECTION_INPUT, 0});
    return ReturnCode::OK;
}

ReturnCode bucket::read(float& fRain)
{
    bool val = m_oLine.get_value();
    if (val && val != m_bState)
    {
        fRain += 0.2f * static_cast<float>(val);
    }
    m_bState = val;
    return ReturnCode::OK;
}

bucket::~bucket()
{
    if (m_oLine.is_requested())
        m_oLine.release();
}