#ifndef __HTTP_COMM_H__
#define __HTTP_COMM_H__
#include "meteoman.h"
#include <curl/curl.h>
#include <string>
#include <thread>

#include <queue>
#include <semaphore.h>

struct http_data {
  time_t timestamp;
  float temperature;
  float humidity;
  float rain;
};

class http_task_data {
public:
  bool run;
  std::queue<http_data> msg_q;
  sem_t msg_sem;
  std::string url;
};

class http_comm {
public:
  http_comm();
  ~http_comm();
  ReturnCode init(const std::string &sSection);
  ReturnCode send_data(http_data data);

private:
  std::thread m_oThread;
  http_task_data *m_pTaskData;
  static void thread_task(http_task_data *task);
};

#endif //__HTTP_COMM_H__
