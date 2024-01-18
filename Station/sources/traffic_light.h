#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__
#include "meteoman.h"
#include <gpiod.hpp>

class traffic_light
{
public:
    enum state
    {
        XXX = 0x0,
        XXG = 0x1,  
        XYX = 0x2,  
        XYG = 0x3, 
        RXX = 0x4,  
        RXG = 0x5, 
        RYX = 0x6, 
        RYG = 0x7, 
    };
    traffic_light();
    ~traffic_light();
    ReturnCode init(const std::string& sSection);
    ReturnCode set_state(const state light_state);
private:
    gpiod::chip m_oChip;
    gpiod::line m_oGreenLed;
    gpiod::line m_oYellowLed;
    gpiod::line m_oRedLed;
};

#endif //__TRAFFIC_LIGHT_H__ 