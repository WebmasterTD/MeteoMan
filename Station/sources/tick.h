#ifndef __TICK_H_
#define __TICK_H_
#include <inttypes.h>
#include "meteoman.h"

#include <chrono>

// using seconds_t = uint32_t;
// using milliseconds_t = uint32_t;

class tick
{
public:
    ReturnCode init(timeval interval, bool blocking);
    ReturnCode wait();
    bool expired();

private:
    timeval m_nTickInterval;
    bool m_bBlocking;
    int m_nTimerFd;
};

#endif