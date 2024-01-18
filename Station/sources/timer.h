#ifndef __TIMER_H__
#define __TIMER_H__
#include "meteoman.h"
#include <string>

class timer
{
    int64_t m_nWaitTime;
public:
    ReturnCode init(const std::string& sSection);
    void wait();

private:
    time_t get_next_time();
};

#endif //__TIMER_H__