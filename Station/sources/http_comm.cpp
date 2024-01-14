#include "http_comm.h"
#include "fmt/core.h"

ReturnCode http_comm::init(const std::string& sSection)
{
    m_oConfReader = INIReader("config.ini");

    m_sUrl = m_oConfReader.Get(sSection, "url", "");
    m_nIntervalSec = m_oConfReader.GetInteger(sSection, "interval", 60);
    
    struct timeval period
    {
        .tv_sec = m_nIntervalSec, .tv_usec = 0
    };
    Timer.init(period, false);
    State = WAIT_FOR_TIMER;
    return ReturnCode::OK;
}

ReturnCode http_comm::send_data(http_data data)
{
    CURL *curl;
    CURLcode res;
    // curl_easy_reset
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, m_sUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char timestamp_s[20];
        strftime(timestamp_s, sizeof(timestamp_s), "%Y-%m-%d %H:%M:%S", localtime(&data.timestamp));
        std::string msg_body = fmt::format("{{\"timestamp\":\"{}\",\"temperature\":\"{:.2f}\",\"humidity\":\"{:.2f}\",\"rainfall\":\"{:.2f}\"}}", \
                                                timestamp_s,\
                                                data.temperature,\
                                                data.humidity,\
                                                data.rain);
                                                
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg_body.c_str());
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
    {
        fmt::print("HTTP resp: {}\n", curl_easy_strerror(res));
        return ReturnCode::ERROR;
    }
    fmt::print("\n");
    return ReturnCode::OK;
}