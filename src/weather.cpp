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
	prettyCLIPrintTable(serverResponse);
}

void prettyCLIPrintTable(FetchBoyStruct &response)
{
	WeatherStruct weather = convertJsonToStructure(response.message);

	echoRow("Weather for ", 12);
	echoRow(weather.locationName, weather.locationName.length()+1);
	std::cout << ", ";
	echoRow(weather.conditions, COL_WIDTH);
	std::cout << std::endl;
	
	echoRow("Temperature", COL_WIDTH);
	echoRow(weather.temperature.temperature, COL_WIDTH);
	echoRow(weather.temperature.temperatureMinimum, COL_WIDTH);
	echoRow(weather.temperature.temperatureMaximum, COL_WIDTH);
	std::cout << std::endl;

	echoRow("Sun", COL_WIDTH);
	echoRow(weather.sun.sunrise, COL_WIDTH);
	echoRow(weather.sun.sunset, COL_WIDTH);
	std::cout << std::endl;

	echoRow("Pressure", COL_WIDTH);
	echoRow(weather.baro, COL_WIDTH);
	std::cout << std::endl;

	echoRow("Humidity", COL_WIDTH);
	echoRow(weather.humidity, COL_WIDTH);
	std::cout << std::endl;

	echoRow("Visibility", COL_WIDTH);
	echoRow(weather.visibility, COL_WIDTH);
	std::cout << std::endl;

	echoRow("Wind", COL_WIDTH);
	echoRow(weather.wind.speed, COL_WIDTH);
	std::cout << "from";
	echoRow(weather.wind.degrees, COL_WIDTH);
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
	data.visibility = 	jsonObject["visibility"].asString();
	data.wind.degrees = jsonObject["wind"]["degrees"].asInt();
	data.wind.speed =	jsonObject["wind"]["speed"].asFloat();
	data.sun.sunrise = 	jsonObject["sys"]["sunrise"].asString();
	data.sun.sunset = 	jsonObject["sys"]["sunset"].asString();
	data.temperature.temperature = 			jsonObject["main"]["temp"].asFloat();
	data.temperature.temperatureMaximum = 	jsonObject["main"]["temp_max"].asFloat();
	data.temperature.temperatureMinimum = 	jsonObject["main"]["temp_min"].asFloat();

	return data;
}