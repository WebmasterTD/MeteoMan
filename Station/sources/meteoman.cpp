#include "meteoman.h"
#include "INIReader.h"
#include "logic.h"
#include <fmt/core.h>

void InterruptHandler(int signum) {
  fmt::println(stderr, "\ntime to exit! with code {}", signum);
  exit(0);
}

int main(void) {
  signal(SIGINT, InterruptHandler);

  fmt::println("CONFIG FILE PATH: {}", CONFIG_FILE_NAME);

  INIReader ini_file = INIReader(CONFIG_FILE_NAME);
  int ret = ini_file.ParseError();
  if (ret != 0) {
    fmt::println(stderr, "ERROR parsing config file! {}", ret);
    return ret;
  }

  tick main_tick;
  Logic main_logic;
  if (main_logic.init() == ReturnCode::ERROR) {
    return -1;
  }

  INIReader ConfReader(CONFIG_FILE_NAME);
  int32_t interval_ms = ConfReader.GetInteger("MAIN", "interval_ms", 100);

  struct timeval period = {};
  if (interval_ms >= 1000) {
    period.tv_sec = interval_ms / 1000;
    period.tv_usec = (interval_ms % 1000) * 1000;
  } else {
    period.tv_usec = interval_ms * 1000;
  }

  if (main_tick.init(period, true) == ReturnCode::ERROR) {
    return -1;
  }

  while (1) {
    main_logic.loop();
    main_tick.wait();
  }
  return 0;
}
