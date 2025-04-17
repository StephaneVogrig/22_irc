/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AccuWeatherAPI.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AccuWeatherAPI_HPP
# define AccuWeatherAPI_HPP

#include <string>
#include "HttpClient.hpp"

struct WeatherInfo
{
	std::string description;
	float temperature;
};

class AccuWeatherAPI
{
	public:
		AccuWeatherAPI(std::string key);
		~AccuWeatherAPI();

		std::string	get_location_key(const std::string & location);
		WeatherInfo	fetch_current_conditions(const std::string & location);

	private:
		std::string apiKey;
		HttpClient  client;
};

#endif