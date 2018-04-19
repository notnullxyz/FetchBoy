#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include "fetchboy.h"

const std::string APIURL = "api.openweathermap.org/data/2.5/weather?q=";

void getLiveData(const std::string& city, const std::string& apikey);
void prettyCLIPrint(const FetchBoyStruct response);

#endif