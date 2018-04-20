#include "fetchboy.h"

FetchBoy::FetchBoy()
{
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
            fbStruct.status = FAIL;
            fbStruct.message = curl_easy_strerror(result);
        }
        else
        {
            fbStruct.status = OK;
            fbStruct.message = result;
        }

        curl_easy_cleanup(curl);
    }

    return fbStruct;
}

void FetchBoy::setUrl(const std::string& url)
{
    apiPath = url;
}

void FetchBoy::setCity(const std::string& city)
{
    queryCity = city;
}

void FetchBoy::setApiKey(const std::string& apikey)
{
    apiKey = apikey;
}
