#include "bucket.h"
#include <fmt/core.h>
#define BUCKET_PIN 10

uint32_t bucket::m_nCounter = 0;
unsigned int bucket::m_nPinGpio = 0;

void bucket::gpioAlertFunc(int gpio, int level, uint32_t tick)
{
    if ((gpio == m_nPinGpio ) && (level == 1))
    {
        m_nCounter++;
        // fmt::print("rainbucket: signal recieved {}\n", m_nCounter);
    }
}

ReturnCode bucket::init(const std::string& sSection)
{
    m_oConfReader = INIReader(CONFIG_FILENAME);

    m_nPinGpio = m_oConfReader.GetInteger(sSection, "test_pin", -1);
    if (m_nPinGpio == -1)
    {
        return ReturnCode::ERROR;
    }
    if (gpioInitialise() ==  PI_INIT_FAILED)
    {
        return ReturnCode::ERROR;
    }
    gpioSetMode(m_nPinGpio, PI_INPUT);

    gpioSetAlertFunc(m_nPinGpio, &gpioAlertFunc);

    return ReturnCode::OK;
}

ReturnCode bucket::read(float& fRain)
{
    fRain = 0.2 * m_nCounter;
    m_nCounter = 0;
    return ReturnCode::OK;
}

bucket::~bucket()
{
    gpioTerminate();
}