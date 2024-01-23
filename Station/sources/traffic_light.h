#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__
#include "meteoman.h"
#include <gpiod.hpp>

class traffic_light
{
public:
    traffic_light();
    ~traffic_light();
    ReturnCode init(const std::string& sSection);
    ReturnCode clear();
    ReturnCode Red(bool state);
    ReturnCode Yellow(bool state);
    ReturnCode Green(bool state);
private:
    gpiod::chip m_oChip;
    gpiod::line m_oGreenLed;
    gpiod::line m_oYellowLed;
    gpiod::line m_oRedLed;
};

#endif //__TRAFFIC_LIGHT_H__ 