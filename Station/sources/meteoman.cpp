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
    

    struct timeval period
    {
        .tv_sec = 5, .tv_usec = 0
    };

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