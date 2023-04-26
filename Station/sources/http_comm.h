#ifndef __HTTP_COMM_H__
#define __HTTP_COMM_H__
#include "meteoman.h"
#include <curl/curl.h>
#include <string>
#include "INIReader.h"


class http_comm
{
public:
    http_comm():m_pCurl(nullptr) {};
    ~http_comm();
    ReturnCode init(const std::string& sSection);
    ReturnCode send_data();
private:
    CURL* m_pCurl;
    std::string m_sUrl;
    INIReader m_oConfReader;
};

#endif //__HTTP_COMM_H__