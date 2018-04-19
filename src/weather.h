#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include "fetchboy.h"

void getLiveData(const std::string& city, const std::string& apikey);
void prettyCLIPrint(const FetchBoyStruct response);

#endif