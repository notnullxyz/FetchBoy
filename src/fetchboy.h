#ifndef FETCHBOY_H
#define FETCHBOY_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

enum status_t {
    FETCHBOY_OK = 0,
    FETCHBOY_FAIL = 1
};

struct FetchBoyStruct
{
    status_t status;
    std::string message;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

const std::string FETCHBOY_CORE_VERSION = "1.1";
const signed long FETCHBOY_CURL_TIMEOUT = 5000L;
const std::string FETCHBOY_USER_AGENT = "FetchBoy-agent/" + FETCHBOY_CORE_VERSION;

class FetchBoy
{

  private:
    std::string apiPath;
    std::string apiKey;
    std::string queryCity;
    std::string outputBody;

    //static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

  public:
    FetchBoy();

    /**
     * Mutator for API URL
     */
    void setUrl(const std::string& url);

    /**
     * Mutator for City
     */
    void setCity(const std::string& city);

    /**
     * Mutator for API KEY
     */
    void setApiKey(const std::string& apikey);
    
    FetchBoyStruct getCurrent();

};

#endif