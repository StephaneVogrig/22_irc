/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:24:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 14:50:16 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* constructor ---------------------------------------------------------------*/

Bot::Bot(int port, const std::string & password_irc)
	:	_meteo(get_api_key()),
		_password_irc(password_irc),
		_nickname(BOT_NICKNAME),
		_channel_name("#" BOT_NICKNAME),
		_delimiter_irc("\r\n")
{
	_socket_irc = create_socket();
	struct sockaddr_in addr_irc;
	addr_irc.sin_family = AF_INET;
	addr_irc.sin_port = htons(port);
	if (inet_pton(AF_INET, "127.0.0.1", &addr_irc.sin_addr) <= 0)
	{
		close(_socket_irc);
		throw (std::runtime_error(FG_RED"bad ip" RESET));
	}
	if (connect(_socket_irc, (struct sockaddr *)&addr_irc, sizeof(addr_irc)) < 0)
	{
		close(_socket_irc);
		throw (std::runtime_error(FG_RED "connect failed" RESET));
	}
}

/* destructor ----------------------------------------------------------------*/

Bot::~Bot()
{
	close(_socket_irc);
}

/* public utilities ----------------------------------------------------------*/

void Bot::run()
{
	while (true)
		process_irc_msg(Message(get_next_msg()));
}

std::string Bot::get_api_key()
{
	std::ifstream file("api_key");
	if (!file.is_open())
		throw std::runtime_error("get_api_key: Error opening api_key file");
	std::string key;
	std::getline(file, key);
	file.close();
	if (key.empty())
		throw std::runtime_error("get_api_key: api_key file is empty");
	return key;
}

#define LOCATION_NOT_FOUND "Location not found"
#define INVALID_API_KEY "Invalid API key. Contact the administrator."

void Bot::send_meteo(const std::string & location)
{
	if (location.empty())
	{
		send_privmsg(LOCATION_NOT_FOUND);
		return ;
	}

	std::string location_key = _meteo.get_location_key(location);
	if (location_key.empty())
	{
		send_privmsg(LOCATION_NOT_FOUND);
		return ;
	}
	else if (location_key == "Unauthorized")
	{
		send_privmsg(INVALID_API_KEY);
		return ;
	}

	WeatherInfo info = _meteo.fetch_current_conditions(location_key);
	if (info.description == "Unauthorized")
	{
		send_privmsg(INVALID_API_KEY);
		return ;
	}
	std::string location_upper(location);
	for(std::string::iterator it = location_upper.begin(); it <= location_upper.end(); ++it)
		*it = std::toupper(*it);

	send_privmsg("Weather for: " + location_upper);
	send_privmsg("Conditions : " + info.description);
	send_privmsg("Temperature: " + info.temperature + "°C");
	send_privmsg("Humidity   : " + info.humidity + "%");
	send_privmsg("Pressure   : " + info.pressure + " mb");
	send_privmsg("Visibility : " + info.visibility + " km");
	send_privmsg("Wind       : " + info.wind_speed + " km/h from " + info.wind_direction);
	send_privmsg("Wind gusts : " + info.wind_gust + " km/h");
	send_privmsg("UV Index   : " + info.uv_index + " (" + info.uv_index_text + ")");
}

void Bot::process_irc_msg(const Message & msg)
{
	if (msg.get_command() == "JOIN")
	send_privmsg("Welcome to meteobot. Write the name of the city you want have the meteo");
	else if (msg.get_command() == "PRIVMSG")
		send_meteo(msg.get_params().get_param(1));
}

void Bot::send_to_irc(const std::string & msg)
{
	std::string msg_irc = ":" + _nickname + " " + msg + _delimiter_irc;
	if (send(_socket_irc, msg_irc.c_str(), msg_irc.length(), MSG_NOSIGNAL) == -1)
	{
		check_sigint();
		throw std::runtime_error(FG_RED "send_to_irc: send error: " RESET + std::string(strerror(errno)));
	}
}

void Bot::send_privmsg(const std::string & msg)
{
	send_to_irc("PRIVMSG " + _channel_name + " :" + msg);
}

std::string Bot::get_next_msg()
{
	std::size_t pos = _buffer.find(_delimiter_irc);
	while (pos == std::string::npos)
	{
		char temp[512];
		memset(temp, 0, sizeof(temp));
		int size_read = recv(_socket_irc, &temp, sizeof(temp), MSG_NOSIGNAL);

		// handle errors
		if (size_read == 0)
			throw (std::runtime_error(FG_PURPLE"Server closed" RESET));
		else if (size_read == -1)
		{
			check_sigint();
			throw std::runtime_error(FG_RED "get_next_msg: recv error: " RESET + std::string(strerror(errno)));
		}

		// handle data
		std::string receive(temp, size_read);
		pos = receive.find(_delimiter_irc);
		if (pos == std::string::npos)
			_buffer += receive;
		else
		{
			std::string result = _buffer + receive.substr(0, pos);
			_buffer = receive.substr(pos + _delimiter_irc.length());
			return result;
		}
	}
	std::string result = _buffer.substr(0, pos);
	_buffer = _buffer.substr(pos + _delimiter_irc.length());
	return result;
}

void Bot::authentication()
{
	send_to_irc("PASS " + _password_irc);
	send_to_irc("NICK " + _nickname);
	send_to_irc("USER " + _nickname + " 0 * :" + _nickname);

	std::string receive = get_next_msg();

	if (receive.find("001") == std::string::npos)
		throw (std::runtime_error(FG_RED"authentication failed" RESET));

	send_to_irc("JOIN " + _channel_name);
	receive = get_next_msg();

	if (receive.find("JOIN") == std::string::npos)
		throw (std::runtime_error(FG_RED"join channel failed" RESET));
	receive = get_next_msg();

	if (receive.find("353") == std::string::npos)
		throw (std::runtime_error(FG_RED"join channel failed" RESET));

	receive = get_next_msg();
	if (receive.find("366") == std::string::npos)
		throw (std::runtime_error(FG_RED"join channel failed" RESET));
}

void Bot::check_sigint()
{
	if (g_sigint)
		throw std::runtime_error(FG_PURPLE "\rBot closed" RESET);
}
