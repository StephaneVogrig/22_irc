/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AccuWeatherAPI.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 14:03:59 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AccuWeatherAPI.hpp"

/* constructor ---------------------------------------------------------------*/

AccuWeatherAPI::AccuWeatherAPI(std::string key)
	: _apiKey(key)
{
	if (!is_key_valid())
		throw std::runtime_error("Invalid API key");
}

/* destructor ----------------------------------------------------------------*/

AccuWeatherAPI::~AccuWeatherAPI()
{}

/* public utilities ----------------------------------------------------------*/

std::string extract_json(const std::string & http_response)
{
	size_t json_start = http_response.find("\r\n\r\n");
	if (json_start == std::string::npos)
		return "";
	return http_response.substr(json_start + 4);
}

std::string extract_value(const std::string & json, const std::string & key)
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

std::string extract_num_value(const std::string & json, const std::string & key)
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

std::string str_to_url(const std::string & str)
{
	std::ostringstream oss;
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (isalnum(*it) || *it == '-' || *it == '_' || *it == '.' || *it == '~')
			oss << *it;
		else
			oss << '%' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << int(static_cast<unsigned char>(*it));
	}
	return oss.str();
}

std::string AccuWeatherAPI::get_location_key(const std::string & location)
{
	log_("Asking location key for: " + location);
	std::string path = "/locations/v1/cities/search?apikey=" + _apiKey + "&q=" + str_to_url(location);
	std::string host = "dataservice.accuweather.com";
	std::string json = get_json(host, path);
	if (json == "Unauthorized")
		return "Unauthorized";

	std::string location_code = extract_value(json, "Key");
	return location_code;
}

WeatherInfo AccuWeatherAPI::fetch_current_conditions(const std::string & location_code)
{
	log_("Asking current condition for: " + location_code);
	std::string path = "/currentconditions/v1/" + location_code + "?apikey=" + _apiKey + "&details=true";
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

AccuWeatherAPI::Accu_error::Accu_error(const std::string & msg) : std::runtime_error(msg)
{}

/* private utilities ----------------------------------------------------------*/

std::string AccuWeatherAPI::http_get(const std::string & host, const std::string & path)
{
	// Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		log_("http_get: socket error: " + std::string(strerror(errno)));
		throw Accu_error("Unable to respond to your request due to an internal error (socket)");
	}

	// Resolve the host
	struct addrinfo		hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	struct addrinfo *	result;

	int error = getaddrinfo(host.c_str(), "80", &hints, &result);
	if (error != 0)
	{
		close(sockfd);
		log_("http_get: getaddrinfo error: " + to_string(error));
		throw Accu_error("Unable to respond to your request due to an internal error (getaddrinfo)");
	}

	// Connect to the server
	if (connect(sockfd, result->ai_addr, result->ai_addrlen) == -1)
	{
		freeaddrinfo(result);
		close(sockfd);
		log_("http_get: connect error: " + std::string(strerror(errno)));
		throw Accu_error("Unable to respond to your request due to an internal error (connect)");
	}

	freeaddrinfo(result);

	// Prepare the HTTP GET request
	std::string request =   "GET " + path + " HTTP/1.1\r\n" +
							"Host: " + host + "\r\n" +
							"Connection: close\r\n\r\n";

	if (send(sockfd, request.c_str(), request.size(), 0) == -1)
	{
		close(sockfd);
		log_("http_get: send error: " + std::string(strerror(errno)));
		throw Accu_error("Unable to respond to your request due to an internal error (send)");
	}

	// Read the response
	std::string response;
	char buffer[4096];
	int size_buffer = sizeof(buffer);
	int size_read;
	do
	{
		memset(&buffer, 0, size_buffer);
		size_read = recv(sockfd, buffer, size_buffer - 1, 0);
		if (size_read == -1)
		{
			close(sockfd);
			log_("http_get: recv error: " + std::string(strerror(errno)));
			throw Accu_error("Unable to respond to your request due to an internal error (recv)");
		}
		response += buffer;
	}
	while (size_read == size_buffer);

	close(sockfd);

	return response;
}

std::string AccuWeatherAPI::get_json(const std::string & host, const std::string & path)
{
	std::string response = http_get(host, path);
	if (response.find("Unauthorized") != std::string::npos)
		return "Unauthorized";
	std::string json = extract_json(response);
	return json;
}

bool AccuWeatherAPI::is_key_valid()
{
	std::string response = http_get("dataservice.accuweather.com",
		"/locations/v1/cities/search?apikey=" + _apiKey + "&q=Paris");

	if (response.find("Unauthorized") != std::string::npos)
		return false;
	return true;
}
