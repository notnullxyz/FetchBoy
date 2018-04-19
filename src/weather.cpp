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
	FetchBoyStruct temp = fetchboy.getCurrent();
	prettyCLIPrint(temp);
}

void prettyCLIPrint(const FetchBoyStruct response)
{
	// format and prettify
	std::cout << std::endl << "Status: " << response.status << ", Temp: " << response.message << std::endl;
}