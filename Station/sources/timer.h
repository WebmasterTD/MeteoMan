#ifndef __TIMER_H__
#define __TIMER_H__
#include "meteoman.h"
#include <string>
#include "INIReader.h"

class timer
{
    // uint m_nMinutes;
    int64_t m_nWaitTime;
    INIReader m_oConfReader;
public:
    ReturnCode init(const std::string& sSection);
    void wait();

private:
    time_t get_next_time();
};

#endif //__TIMER_H__