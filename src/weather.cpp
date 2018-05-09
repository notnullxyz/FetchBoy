#include "weather.h"

FetchBoy fetchboy;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cout << "Usage: FetchBoy <openweather apikey> <city>" << std::endl;
		return 1;
	}

	getLiveData(argv[2], argv[1]);
	return 0;
}

void getLiveData(const std::string& city, const std::string& apikey)
{	
	fetchboy.setApiKey(apikey);
	fetchboy.setCity(city);
	fetchboy.setUrl(APIURL);
	FetchBoyStruct serverResponse = fetchboy.getCurrent();
	prettyCLIPrint(serverResponse);
}

void prettyCLIPrint(FetchBoyStruct &response)
{
	//std::cout << "DEBUG status: " << response.status << std::endl << "DEBUG message: " << response.message << std::endl;
	// handle error specifics here... then call out to beautify the Json
	//weatherDataMap m = makeJsonReadable(response.message);
	WeatherStruct weather = convertJsonToStructure(response.message);

	//std::cout << weather.locationName << std::endl;
	//std::cout << weather.sun.sunrise << std::endl;

	echoRow("Location", 20);
	echoRow("Sunrise", 20);
	std::cout << std::endl;
	echoRow(weather.locationName, 20);
	echoRow(weather.sun.sunrise, 20);
	std::cout << std::endl;
}

/**
 * Pretty output formatter template for final weather data display
 */
template<typename T> void echoRow(T t, const int & width) {
	std::cout << std::left << std::setw(width) << std::setfill(SEPARATOR) << t;
}

/**
 * Convert from JSON to whatever is considered 'readable' here.
 * Room for some polymorph perhaps, depending on where this is compiled from/for.
 */
WeatherStruct convertJsonToStructure(std::string &json) {
	Json::Reader jsonReader;
	Json::Value jsonObject;
	WeatherStruct data;

	jsonReader.parse(json, jsonObject);

	// pack the known response from weather service into my own struct
	data.locationName = jsonObject["name"].asString();
	data.conditions = 	jsonObject["weather"][0]["description"].asString();
	data.baro = 		jsonObject["main"]["pressure"].asInt();
	data.humidity = 	jsonObject["main"]["humidity"].asInt();
	data.visibility = 	jsonObject["visibility"].asInt();
	data.wind.degrees = jsonObject["wind"]["degrees"].asInt();
	data.wind.speed =	jsonObject["wind"]["speed"].asFloat();
	data.sun.sunrise = 	jsonObject["sys"]["sunrise"].asString();
	data.sun.sunset = 	jsonObject["sys"]["sunset"].asString();
	data.temperature.temperature = 			jsonObject["main"]["temperature"].asFloat();
	data.temperature.temperatureMaximum = 	jsonObject["main"]["temp_max"].asFloat();
	data.temperature.temperatureMinimum = 	jsonObject["main"]["temp_min"].asFloat();

	return data;
}