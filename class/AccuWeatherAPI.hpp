/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AccuWeatherAPI.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/22 17:16:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AccuWeatherAPI_HPP
# define AccuWeatherAPI_HPP

#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <netdb.h>
#include <unistd.h>

#include "log.hpp"

struct WeatherInfo
{
	std::string description;
	std::string temperature;
	std::string wind;
	std::string humidity;
	std::string pressure;
	std::string visibility;
	std::string wind_speed;
	std::string wind_direction;
	std::string wind_gust;
	std::string uv_index;
	std::string uv_index_text;
};

class AccuWeatherAPI
{
	public:
		AccuWeatherAPI(std::string key);
		~AccuWeatherAPI();

		std::string	get_location_key(const std::string & location);
		WeatherInfo	fetch_current_conditions(const std::string & location_code);
		class Accu_error : public std::runtime_error
		{
			public:
				Accu_error(const std::string & msg);
		};

	private:

		std::string http_get(const std::string& host, const std::string& path);
		std::string get_json(const std::string & host, const std::string & path);
		bool is_key_valid();

		std::string _apiKey;

};

#endif