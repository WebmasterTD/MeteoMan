#ifndef __BUCKET_H__
#define __BUCKET_H__
#include "meteoman.h"
// #include <gpiod.h>
#include <pigpio.h>
#include "INIReader.h"

class bucket
{
public:
    ~bucket();
    ReturnCode init(const std::string& sSection);
    ReturnCode read(float& fRain);
    
private:
    static uint32_t m_nCounter;
    static void gpioAlertFunc(int gpio, int level, uint32_t tick);
    static unsigned int m_nPinGpio;
    INIReader m_oConfReader;

};
#endif