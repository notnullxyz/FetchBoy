#include "fetchboy.h"

FetchBoy::FetchBoy()
{
}

FetchBoyStruct FetchBoy::parseResponse(void)
{
    std::cout << "parseResponse not implemented" << std::endl;
}

FetchBoyStruct FetchBoy::getCurrent()
{
    CURL *curl;
    CURLcode result;
    FetchBoyStruct fbStruct;
    std::ostringstream ss;

    curl = curl_easy_init();
    if (curl)
    {
        ss << apiPath << queryCity << "&APPID=" << apiKey;
        std::string queryUrl = ss.str();

        curl_easy_setopt(curl, CURLOPT_URL, queryUrl);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // can follow redirect

        result = curl_easy_perform(curl); // execute request

        if (result != CURLE_OK)
        {
            fprintf(stderr, "FetchBoy didn't make it back :(\t %s\n", curl_easy_strerror(result));
            fbStruct.tempCelsius = 0;
            fbStruct.status = FAIL;
        }
        else
        {
            fbStruct.tempCelsius = 999;
            fbStruct.status = OK;
        }

        curl_easy_cleanup(curl);
    }

    return fbStruct;
}

void FetchBoy::setUrl(const char *url)
{
    strcpy(apiPath, url);
}

void FetchBoy::setCity(const char *city)
{
    strcpy(queryCity, city);
}

void FetchBoy::setApiKey(const char *apikey)
{
    strcpy(apiKey, apikey);
}
