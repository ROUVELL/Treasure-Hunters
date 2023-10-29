#include "Settings.h"

Settings::Settings()
{

	std::ifstream file(".\\res\\settings.json");

	if (!file.is_open())
	{
		Logger::logError("SETTINGS: Can`t open the settings json file!");
		return;
	}

	file >> json;

	//std::cout << json << "\n";
	//std::cout << file.is_open() << "\n";

	file.close();
}
