#include "fetchboy.h"

FetchBoy::FetchBoy()
{
}

FetchBoyStruct FetchBoy::getCurrent(const std::string& unit)
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
        ss << apiPath << queryCity << "&units=" << unit << "&APPID=" << apiKey;
        std::string queryUrl = ss.str();
        char* apiUrl = new char [queryUrl.length()+1];
        std::strcpy(apiUrl, queryUrl.c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, "");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, FETCHBOY_CURL_TIMEOUT);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // can follow redirect
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 2 ); // timeout for dns cache
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);   // IP version to resolve to
        curl_easy_setopt(curl, CURLOPT_USERAGENT, FETCHBOY_USER_AGENT);

        // write response to our write call back
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outputBody);

        result = curl_easy_perform(curl);
        delete[] apiUrl;

        curl_easy_cleanup(curl);

        if (result != CURLE_OK)
        {
            std::string exception = "FetchBoyCurlException, FetchBoy did not make it back :( - ";
            exception.append(curl_easy_strerror(result));
            throw exception;
        }
        else
        {
            fbStruct.status = FETCHBOY_OK;
            fbStruct.message = outputBody;
        }

        
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

/**
 * Write callback for curl response.
 * Lifted from
 * @see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}