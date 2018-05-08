#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include "fetchboy.h"
#include <jsoncpp/json/json.h>
#include <map>

const std::string APIURL = "api.openweathermap.org/data/2.5/weather?q=";

typedef std::map<std::string, std::string> weatherDataMap;

void getLiveData(const std::string& city, const std::string& apikey);
void prettyCLIPrint(FetchBoyStruct &response);
weatherDataMap makeJsonReadable(std::string &json);

#endif