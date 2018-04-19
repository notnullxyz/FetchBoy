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
    char *apiPath;
    char *apiKey;
    char *queryCity;

    FetchBoyStruct parseResponse(void);

  public:
    FetchBoy();

    /**
     * Mutator for API URL
     */
    void setUrl(const char *url);

    /**
     * Mutator for City
     */
    void setCity(const char *city);

    /**
     * Mutator for API KEY
     */
    void setApiKey(const char *apikey);
    
    FetchBoyStruct getCurrent();

};

#endif