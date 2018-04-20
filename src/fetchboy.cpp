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
        // build a oss of the whole api url, then convert it to a char* for curl.
        // curlopt url expects a char*... this is not an ideal fix.
        ss << apiPath << queryCity << "&APPID=" << apiKey;
        std::string queryUrl = ss.str();
        char * apiUrl = new char [queryUrl.length()+1];
        std::strcpy(apiUrl, queryUrl.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, apiUrl);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // can follow redirect
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, false );
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 2 );
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

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
