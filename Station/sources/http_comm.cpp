#include "http_comm.h"
#include "fmt/core.h"
#include "INIReader.h"

http_comm::http_comm()
{
    m_pTaskData = new http_task_data;
}
http_comm::~http_comm()
{
    delete m_pTaskData;
}

void http_comm::thread_task(http_task_data *task)
{
    fmt::println("From another thread!");
    CURL *curl;
    curl = curl_easy_init();

    if (curl)
    {
        while (task->run)
        {
            sem_wait(&task->msg_sem);
            while (!task->msg_q.empty())
            {
                http_data data = task->msg_q.front();
                task->msg_q.pop();

                fmt::println("http data recieved!");

                curl_easy_reset(curl);
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                curl_easy_setopt(curl, CURLOPT_URL, task->url.c_str());
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
                struct curl_slist *headers = NULL;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

                char timestamp_s[20];
                strftime(timestamp_s, sizeof(timestamp_s), "%Y-%m-%d %H:%M:%S", localtime(&data.timestamp));
                std::string msg_body = fmt::format("{{\"timestamp\":\"{}\",\"temperature\":\"{:.2f}\",\"humidity\":\"{:.2f}\",\"rainfall\":\"{:.2f}\"}}",
                                                   timestamp_s,
                                                   data.temperature,
                                                   data.humidity,
                                                   data.rain);

                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg_body.c_str());
                CURLcode res = curl_easy_perform(curl);

                if (res != CURLE_OK)
                {
                    fmt::println(stderr, "HTTP - {}", curl_easy_strerror(res));
                }
                fmt::print("\n");
            }
        }
        curl_easy_cleanup(curl);
    }
}

ReturnCode http_comm::init(const std::string &sSection)
{
    INIReader ConfReader("config.ini");
    // m_sUrl = ConfReader.Get(sSection, "url", "");
    m_nIntervalSec = ConfReader.GetInteger(sSection, "interval_s", 60);

    struct timeval period
    {
        .tv_sec = m_nIntervalSec, .tv_usec = 0
    };
    Timer.init(period, false);
    sem_init(&m_pTaskData->msg_sem, 1, 0);
    m_pTaskData->url = ConfReader.Get(sSection, "url", "");
    m_pTaskData->run = true;
    m_oThread = std::thread(thread_task, m_pTaskData);

    return ReturnCode::OK;
}

ReturnCode http_comm::send_data(http_data data)
{
    m_pTaskData->msg_q.push(data);
    if (sem_post(&m_pTaskData->msg_sem) != 0)
    {
        return ReturnCode::ERROR;
    }
    return ReturnCode::OK;
}
