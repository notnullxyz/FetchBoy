#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <iomanip>
#include "fetchboy.h"

#include <jsoncpp/json/json.h>

struct Wind {
    float speed;
    int16_t degrees;
};

struct Temperature {
    float temperature;
    float temperatureMinimum;
    float temperatureMaximum;
};

struct Sun {
    std::string sunrise;
    std::string sunset;
};

struct WeatherStruct {
    std::string locationName;
    std::string conditions;
    int16_t baro;
    int16_t humidity;
    int16_t visibility;
    Wind wind;
    Temperature temperature;
    Sun sun;
};

const std::string APIURL = "api.openweathermap.org/data/2.5/weather?q=";

/** 
 * Constant pertaining to the tabular output
 */
const char SEPARATOR = ' ';
const int16_t COL_WIDTH = 15;

void getLiveData(const std::string& city, const std::string& apikey);
void prettyCLIPrint(FetchBoyStruct &response);
WeatherStruct convertJsonToStructure(std::string &json);
template<typename T> void echoRow(T t, const int & width);

#endif