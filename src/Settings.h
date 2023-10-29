#pragma once

#include <fstream>
#include <string>

#include "json.hpp"

#include "Logger.h"


class Settings
{
public:
	Settings();

	template <typename T>
	T get(const char* key) const;

	template <typename T>
	T get(const char* key, T _default) const;

private:
	nlohmann::json json;
};

template<typename T>
inline T Settings::get(const char* key) const
{
	auto it = json.find(key);

	if (it == json.end())
	{
		Logger::logError("SETTINGS: Value by key '" + std::string(key) + "' not found!");
		abort();
		return T{};
	}

	return *it;
}

template<typename T>
inline T Settings::get(const char* key, T _default) const
{
	auto it = json.find(key);

	if (it == json.end())
		return _default;

	return *it;
}

