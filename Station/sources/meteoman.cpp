#include "meteoman.h"
#include "logic.h"
#include "fmt/core.h"

using namespace std::chrono_literals;
using namespace std::chrono;

void InterruptHandler(int signum)
{
    fmt::print(stderr, "\ntime to exit!\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    tick main_tick;
    Logic main_logic;
    if (main_logic.init() == ReturnCode::ERROR)
    {
        return -1;
    }
    signal(SIGINT, InterruptHandler);

    struct timeval period
    {
        .tv_sec = 0, .tv_usec = 500'000
    };
    main_tick.init(period, true);

    struct timeval long_period
    {
        .tv_sec = 120, .tv_usec = 0
    };
    tick helper_tick;
    helper_tick.init(long_period, false);

    while (1)
    {
        main_logic.loop();
        main_tick.wait();

        if (!helper_tick.isActive())
        {
            time_t now = time(nullptr);
            fmt::print("timer expired: {}", ctime(&now));
        }

        // time_t now = time(nullptr);
        // fmt::print("{}", ctime(&now));
    }
    return 0;
}