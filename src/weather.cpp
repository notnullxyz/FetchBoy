#include "weather.h"

FetchBoy fetchboy;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cout << "Usage: FetchBoy <openweather apikey> <city>" << std::endl;
		return 1;
	}

	std::cout << argv[2] << " + " << argv[1];

	getLiveData(argv[2], argv[1]);
	return 0;
}

void getLiveData(const char* city, const char* apikey)
{	
	std::cout << "^^^^^";
	// hardcoded api url... @todo : fix this bad practice :(
	const char* apiurl = "api.openweathermap.org/data/2.5/weather?q=";

	std::cout << "****";	
	fetchboy.setApiKey(apikey);
	std::cout << "!!!!!";
	fetchboy.setCity(city);
	fetchboy.setUrl(apiurl);
	FetchBoyStruct temp = fetchboy.getCurrent();
	prettyCLIPrint(temp);
}

void prettyCLIPrint(const FetchBoyStruct response)
{
	// format and prettify
	std::cout << std::endl << "Status: " << response.status << ", Temp: " << response.tempCelsius << std::endl;
}