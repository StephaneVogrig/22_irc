/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AccuWeatherAPI.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/18 21:20:57 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AccuWeatherAPI.hpp"

/* constructor ---------------------------------------------------------------*/

AccuWeatherAPI::AccuWeatherAPI(std::string key)
	: _apiKey(key), _client()
{
	// if (!is_key_valid())
	// 	throw std::runtime_error("Invalid API key");
}

/* destructor ----------------------------------------------------------------*/

AccuWeatherAPI::~AccuWeatherAPI()
{}

/* public utilities ----------------------------------------------------------*/

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

std::string extract_num_value(const std::string& json, const std::string& key)
{
	std::string pattern = key;
	size_t start = json.find(pattern);
	if (start == std::string::npos)
		return "";
	start += pattern.length();
	size_t end = json.find(",", start);
	if (end == std::string::npos)
		return "";
	return json.substr(start, end - start);
}

std::string AccuWeatherAPI::get_location_key(const std::string & location)
{
	std::string path = "/locations/v1/cities/search?apikey=" + _apiKey + "&q=" + location;
	std::string host = "dataservice.accuweather.com";
	std::string json = get_json(host, path);
	if (json == "Unauthorized")
		return "Unauthorized";

	std::string locationCode = extract_value(json, "Key");
	return locationCode;
}

WeatherInfo AccuWeatherAPI::fetch_current_conditions(const std::string & location)
{
	std::string path = "/currentconditions/v1/" + location + "?apikey=" + _apiKey + "&details=true";
	std::string host = "dataservice.accuweather.com";
	std::string json = get_json(host, path);
	

	WeatherInfo info;
	if (json == "Unauthorized")
	{
		info.description = "Unauthorized";
		return info;
	}
	
	info.description = extract_value(json, "WeatherText");
	info.temperature = extract_num_value(json, "\"Metric\":{\"Value\":");
	info.humidity = extract_num_value(json, "\"RelativeHumidity\":");
	info.pressure = extract_num_value(json, "\"Pressure\":{\"Metric\":{\"Value\":");
	info.visibility = extract_num_value(json, "\"Visibility\":{\"Metric\":{\"Value\":");
	info.wind_speed = extract_num_value(json, "\"Speed\":{\"Metric\":{\"Value\":");
	info.wind_direction = extract_value(json, "Localized");
	info.wind_gust = extract_num_value(json, "\"WindGust\":{\"Speed\":{\"Metric\":{\"Value\":");
	info.uv_index = extract_num_value(json, "\"UVIndex\":");
	info.uv_index_text = extract_value(json, "UVIndexText");
	return info;
}

/* private utilities ----------------------------------------------------------*/

std::string AccuWeatherAPI::get_json(const std::string & host, const std::string & path)
{
	std::string response = _client.get(host, path);
	if (response.find("Unauthorized") != std::string::npos)
	{
		// throw std::runtime_error("Invalid API key");
		return "Unauthorized";
	}
	std::string json = extract_json(response);
	return json;
}

bool AccuWeatherAPI::is_key_valid()
{
	std::string response = _client.get("dataservice.accuweather.com",
		"/locations/v1/cities/search?apikey=" + _apiKey + "&q=Paris");

	if (response.find("Unauthorized") != std::string::npos)
		return false;
	return true;
}
