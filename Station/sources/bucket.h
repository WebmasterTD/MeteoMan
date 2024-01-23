#ifndef __BUCKET_H__
#define __BUCKET_H__
#include "meteoman.h"
#include <gpiod.hpp>

class bucket
{
public:
    bucket();
    ~bucket();
    ReturnCode init(const std::string& sSection);
    ReturnCode read(float& fRain);
    
private:
    bool m_bState; 
    gpiod::chip m_oChip;
    gpiod::line m_oLine;
};
#endif