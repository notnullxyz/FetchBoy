#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include "fetchboy.h"

void getLiveData(const char* city, const char* apikey);
void prettyCLIPrint(const FetchBoyStruct response);

#endif