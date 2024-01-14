#ifndef __HTTP_COMM_H__
#define __HTTP_COMM_H__
#include "meteoman.h"
#include <curl/curl.h>
#include <string>
#include "INIReader.h"
#include "tick.h"

struct http_data
{
    time_t timestamp;
    float temperature;
    float humidity;
    float rain;
};


class http_comm
{
public:
    ReturnCode init(const std::string& sSection);
    ReturnCode send_data(http_data data);

    enum HttpStates {
        WAIT_FOR_TIMER,
        SEND_HTTP,
        WAIT_FOR_HTTP,
        GET_REPLY
    };
    
    tick Timer;
    HttpStates State;

private:
    std::string m_sUrl;
    time_t m_nIntervalSec;
    INIReader m_oConfReader;
};

#endif //__HTTP_COMM_H__