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
	std::cout << makeJsonReadable(response.message) << std::endl;
}

/**
 * Convert from JSON to whatever is considered 'readable' here.
 * Room for some polymorph perhaps, depending on where this is compiled from/for.
 */
std::string makeJsonReadable(std::string &json) {
	return json;
}