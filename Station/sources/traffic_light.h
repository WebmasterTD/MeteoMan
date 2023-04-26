#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__
#include "meteoman.h"
#include "INIReader.h"

class traffic_light
{
public:
    enum state
    {
        XXX,
        XXG,  
        XYX,  
        XYG, 
        RXX,  
        RXG, 
        RYX, 
        RYG 
    };
    ~traffic_light();
    ReturnCode init(const std::string& sSection);
    ReturnCode set_state(const state light_state);
private:
    INIReader m_oConfReader;
    int m_nGreenLed;
    int m_nYellowLed;
    int m_nRedLed;
};

#endif //__TRAFFIC_LIGHT_H__ 