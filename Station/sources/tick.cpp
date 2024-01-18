#include "tick.h"
#include <unistd.h>
#include <thread>
#include <sys/timerfd.h>
#include "fmt/core.h"

ReturnCode tick::init(timeval interval, bool blocking)
{
    m_nTickInterval = interval;
    m_bBlocking = blocking;

    if (m_nTimerFd != 0)
    {
        close(m_nTimerFd);
    }
    int tim_flags = 0;
    if (!m_bBlocking)
    {
        tim_flags |= TFD_NONBLOCK;
    }
    m_nTimerFd = timerfd_create(CLOCK_REALTIME, tim_flags);
    if (m_nTimerFd == -1)
    {
        fmt::println(stderr, "timerfd_create! - {}", strerror(errno));
        return ReturnCode::ERROR;
    }
    int tfd_flags = 0;
    struct itimerspec new_value;
    if (m_nTickInterval.tv_sec > 1)
    {
        time_t curr_time = time(nullptr);
        time_t next_time = curr_time - (curr_time % m_nTickInterval.tv_sec) + m_nTickInterval.tv_sec;

        new_value.it_value.tv_sec = next_time;
        new_value.it_value.tv_nsec = (m_nTickInterval.tv_usec * 1000);
        tfd_flags |= TFD_TIMER_ABSTIME;
        tfd_flags |= TFD_TIMER_CANCEL_ON_SET;
    }
    else
    {
        new_value.it_value.tv_sec = m_nTickInterval.tv_sec;
        new_value.it_value.tv_nsec = m_nTickInterval.tv_usec * 1000;
    }

    new_value.it_interval.tv_sec = m_nTickInterval.tv_sec;
    new_value.it_interval.tv_nsec = m_nTickInterval.tv_usec * 1000;

    if (timerfd_settime(m_nTimerFd, tfd_flags, &new_value, NULL) == -1)
    {
        fmt::println(stderr, "timerfd_settime - {}", strerror(errno));
        return ReturnCode::ERROR;
    }
    return ReturnCode::OK;
}

ReturnCode tick::wait()
{
    uint64_t exp = 0;
    ssize_t s = 0;

    do
    {
        s = read(m_nTimerFd, &exp, sizeof(uint64_t));
        if (s == -1)
        {
            int errsv = errno;
            switch (errsv)
            {
            case EINTR:
                break;
            case ECANCELED:
            {
                fmt::println(stderr, "Tick clock time changed");
                ReturnCode ret = this->init(m_nTickInterval, m_bBlocking);
                if (ret != ReturnCode::OK)
                    return ret;
                break;
            }
            default:
                fmt::println(stderr, "error read timerfd {} {}", s, strerror(errsv));
                return ReturnCode::ERROR;
            }
        }
    } while (s != sizeof(uint64_t));

    if (exp != 1)
    {
        fmt::println(stderr, "cycletime exceeded tick rate: {}!", exp);
        return ReturnCode::ERROR;
    }

    return ReturnCode::OK;
}

bool tick::expired()
{
    uint64_t exp = 0;
    ssize_t s = 0;

    s = read(m_nTimerFd, &exp, sizeof(uint64_t));
    if (s == -1)
    {
        int errsv = errno;
        switch (errsv)
        {
            case EAGAIN:
                break;
            default:
                fmt::println(stderr, "error read timerfd {} {}", s, strerror(errsv));
        }
    }

    return (exp != 0);
}