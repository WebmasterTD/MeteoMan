#include "http_comm.h"
#include <values.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

ReturnCode http_comm::init(const std::string& sSection)
{
    m_oConfReader = INIReader("config.ini");

    m_sUrl = m_oConfReader.Get(sSection, "url", "");
    m_pCurl = curl_easy_init();
    if(m_pCurl)
    {
        // CURLcode res;
        return ReturnCode::OK;
    }
    return ReturnCode::ERROR;
}

ReturnCode http_comm::send_data()
{
    std::string readBuffer;
    CURLcode res;
    curl_easy_setopt(m_pCurl, CURLOPT_URL, m_sUrl.c_str());
    curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, "name=rainman");
    curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(m_pCurl);
    // curl_easy_cleanup(m_pCurl);
    return res == 0 ? ReturnCode::OK : ReturnCode::ERROR;
}

http_comm::~http_comm()
{
    curl_easy_cleanup(m_pCurl);
}