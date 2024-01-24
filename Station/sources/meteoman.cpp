#include "meteoman.h"
#include "logic.h"
#include "INIReader.h"
#include <fmt/core.h>

using namespace std::chrono_literals;
using namespace std::chrono;

void InterruptHandler(int signum)
{
    fmt::println(stderr, "\ntime to exit! with code {}", signum);
    exit(0);
}

int main(void)
{
    
    tick main_tick;
    Logic main_logic;
    if (main_logic.init() == ReturnCode::ERROR)
    {
        return -1;
    }
    
    INIReader ConfReader(CONFIG_FILENAME);
    int32_t interval_ms = ConfReader.GetInteger("MAIN", "interval_ms", 100);

    struct timeval period = {};
    if (interval_ms >= 1000)
    {
        period.tv_sec = interval_ms / 1000;
        period.tv_usec = (interval_ms % 1000) * 1000;
    }
    else
    {
        period.tv_usec = interval_ms * 1000;
    }

    if (main_tick.init(period, true) == ReturnCode::ERROR)
    {
        return -1;
    }

    signal(SIGINT, InterruptHandler);
    
    while (1)
    {
        main_logic.loop();
        main_tick.wait();
    }
    return 0;
}