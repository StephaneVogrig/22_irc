/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AccuWeatherAPI.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/18 00:00:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AccuWeatherAPI.hpp"

AccuWeatherAPI::AccuWeatherAPI(std::string key)
	: _apiKey(key), _client()
{
	std::cout << "API Key: " << _apiKey << std::endl;
}

AccuWeatherAPI::~AccuWeatherAPI()
{}

std::string extract_json(const std::string& http_response)
{
	size_t json_start = http_response.find("\r\n\r\n");
	if (json_start == std::string::npos)
		return "";
	return http_response.substr(json_start + 4);
}

std::string extract_value(const std::string& json, const std::string& key)
{
	std::string pattern = "\"" + key + "\":\"";
	size_t start = json.find(pattern);
	if (start == std::string::npos)
		return "";
	start += pattern.length();
	size_t end = json.find("\"", start);
	if (end == std::string::npos)
		return "";
	return json.substr(start, end - start);
}

std::string AccuWeatherAPI::get_location_key(const std::string & location)
{
	std::string path = "/locations/v1/cities/search?apikey=" + _apiKey + "&q=" + location;
	std::string response = _client.get("dataservice.accuweather.com", path);

	std::string json = extract_json(response);
	std::string locationCode = extract_value(json, "Key");
	return locationCode;
}

WeatherInfo AccuWeatherAPI::fetch_current_conditions(const std::string & location)
{
	std::string path = "/currentconditions/v1/" + location + "?apikey=" + _apiKey;
	std::string response = _client.get("dataservice.accuweather.com", path);

	std::cout << "Response: " << response << std::endl;
	// std::string json = extract_json(response);
	WeatherInfo info;
	info.description = "No description available";
	// info.description = extract_value(json, "WeatherText");
	// info.temperature = std::stof(extract_nested_value(json, "Temperature", "Metric", "Value"));
	return info;
}
