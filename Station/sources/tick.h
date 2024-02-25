#ifndef __TICK_H_
#define __TICK_H_
#include "meteoman.h"
#include <bits/types/struct_timeval.h>
// using seconds_t = uint32_t;
// using milliseconds_t = uint32_t;

class tick {
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
