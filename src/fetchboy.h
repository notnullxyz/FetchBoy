#ifndef FETCHBOY_H
#define FETCHBOY_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

enum status_t {
    OK = 0,
    FAIL = 1
};

struct FetchBoyStruct
{
    int tempCelsius;
    status_t status;
};

class FetchBoy
{

  private:
    std::string apiPath;
    std::string apiKey;
    std::string queryCity;

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