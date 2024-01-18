#include "timer.h"
#include "INIReader.h"
#include <ctime>
#include <unistd.h>
#include <thread> 
#include <chrono>

ReturnCode timer::init(const std::string& sSection)
{
    INIReader ConfReader(CONFIG_FILENAME);

    long nInterval = ConfReader.GetInteger(sSection, "interval", -1);
    m_nWaitTime  = nInterval * 60;

    return ReturnCode::OK;
}

time_t timer::get_next_time()
{
    time_t time_cur = time(nullptr);
    time_t over = time_cur % m_nWaitTime;
    time_t time_fut = (time_cur - over) + m_nWaitTime;
    return time_fut;
}

void timer::wait()
{
    auto sleep_tp = std::chrono::system_clock::from_time_t(get_next_time());
    std::this_thread::sleep_until(sleep_tp);
    return;
}