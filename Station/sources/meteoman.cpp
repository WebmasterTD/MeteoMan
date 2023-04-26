#include "logic.h"
//#include <logger.hpp>

void InterruptHandler(int signum)
{
    exit(0);
}

int main(int argc, char * argv[])
{
    // LOGGER.register_target();
    // LOGGER.init(LogLevel::DEBUG);
    // LOGGER.log(LogLevel::INFO, "Starting MeteoMan");

    Logic main_logic;
    if (main_logic.init() == ReturnCode::ERROR)
    {
        // LOGGER.log(LogLevel::ERROR, "Failed to initialize main_logic");
        return -1;
    }
    signal(SIGINT, InterruptHandler);
    main_logic.loop();
    
    return 0;
}