/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:24:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/18 18:30:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* constructor ---------------------------------------------------------------*/

Bot::Bot(int port, const std::string & password_irc)
	:	_meteo(get_api_key()),
		_password_irc(password_irc),
		_connection_irc_ko(false),
		_nickname(BOT_NICKNAME)
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
	// if (fcntl(_socket_irc, F_SETFL, O_NONBLOCK) == -1)
	// 	throw(std::runtime_error(FG_RED "Bot constructor: fcntl failed: " RESET + std::string(strerror(errno))));
}

/* destructor ----------------------------------------------------------------*/

Bot::~Bot()
{
	close(_socket_irc);
}

/* public utilities ----------------------------------------------------------*/

std::string Bot::get_api_key()
{
	std::ifstream file("api_key");
	if (!file.is_open())
		throw std::runtime_error("Error opening api_key file");
	std::string key;
	std::getline(file, key);
	file.close();
	if (key.empty())
		throw std::runtime_error("Error: api_key file is empty");
	return key;
}

void Bot::send_meteo(const std::string & location)
{
	if (location.empty())
	{
		send_to_irc("PRIVMSG #meteobot :Location not found");
		std::cout << FG_RED "Location not found" RESET << std::endl;
		return ;
	}
	std::string errmsg = "PRIVMSG #meteobot :Location not found";
	std::string location_key = _meteo.get_location_key(location);
	if (location_key.empty() || location_key.find("404") != std::string::npos)
	{
		send_to_irc(errmsg);
		std::cout << FG_RED "Location not found" RESET << std::endl;
		return ;
	}
	WeatherInfo info = _meteo.fetch_current_conditions(location_key);
	if (location_key.empty() || location_key.find("404") != std::string::npos)
	{
		send_to_irc(errmsg);
		std::cout << FG_RED "Location not found" RESET << std::endl;
		return ;
	}
	std::string msg = "PRIVMSG #meteobot :Weather for " + location +
	" | " + info.description +
	" | Temperature: " + info.temperature + "°C" +
	" | Humidity: " + info.humidity + "%" +
	" | Pressure: " + info.pressure + " mb" +
	" | Visibility: " + info.visibility + " km" +
	" | Wind: " + info.wind_speed + " km/h from " + info.wind_direction +
	" (gusts: " + info.wind_gust + " km/h)" +
	" | UV Index: " + info.uv_index + " (" + info.uv_index_text + ")";
	send_to_irc(msg);
}

void Bot::run()
{
	struct pollfd pollfds[1];
	pollfds[0].fd = _socket_irc;
	pollfds[0].events = POLLIN;

	while (true)
	{
		int nbr_event = poll(pollfds, 1, 1);
		if (g_sigint)
		{
			std::cout << FG_PURPLE "\rBot closed" RESET << std::endl;
			break ;
		}
		if( nbr_event == -1)
			throw(std::runtime_error("poll failed"));
		if (nbr_event == 0)
			continue ;
		receive_irc_data();
	}
}

void Bot::process_irc_msg(const Message & msg)
{
	if (msg.get_command() == "JOIN")
		send_to_irc(":meteobot PRIVMSG #meteobot :Welcome to meteobot. Write the name of the city you want have the meteo");
	else if (msg.get_command() == "PRIVMSG")
		send_meteo(msg.get_params().get_param(1));
}

void Bot::receive_irc_data()
{
	static std::string	buffer;
	std::string			delimiter("\r\n");
	char				temp[512];
	while (true)
	{
		ssize_t size_read = recv(_socket_irc, temp, sizeof(temp), MSG_NOSIGNAL);

		// handle errors
		if (size_read == 0)
			throw (std::runtime_error(FG_PURPLE"Server closed" RESET));

		else if (size_read ==  -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break ;
			throw std::runtime_error(FG_PURPLE "receive_irc_data: recv error: " RESET + std::string(strerror(errno)));
		}

		// handle data
		std::string temp_str(temp, size_read);
		size_t start = 0;
		size_t stop = temp_str.find(delimiter);
		if (stop == std::string::npos)
		{
			buffer += temp_str;
			continue;
		}

		// process all complete data
		process_irc_msg(Message(buffer + temp_str.substr(start, stop - start)));
		start = stop + delimiter.length();
		stop = temp_str.find(delimiter, start);
		while (stop != std::string::npos)
		{
			process_irc_msg(Message(temp_str.substr(start, stop - start)));
			start = stop + delimiter.length();
			stop = temp_str.find(delimiter, start);
		}

		// keep remaining data in buffer
		if (start < temp_str.length())
			buffer = temp_str.substr(start);
		else
			buffer.clear();
	}
}

void Bot::send_to_irc(const std::string & msg)
{
	if (_connection_irc_ko)
		return ;
	if(send(_socket_irc, (msg + "\r\n").c_str(), msg.length() + 2, MSG_NOSIGNAL) == -1)
		_connection_irc_ko = true;
}

std::string Bot::get_next_msg()
{
	std::size_t pos = _buffer.find("\r\n");
	while (pos == std::string::npos)
	{
		char buffer[513];
		memset(buffer, 0, sizeof(buffer));
		int size_read = recv(_socket_irc, &buffer, sizeof(buffer) - 1, 0);
		if ( size_read == -1)
			throw (std::runtime_error(strerror(errno)));
		else if ( size_read == 0)
			throw (std::runtime_error(FG_PURPLE"Server closed" RESET));

		std::string receive(buffer);
		pos = receive.find("\r\n");
		if (pos == std::string::npos)
			_buffer += receive;
		else
		{
			std::string result = _buffer + receive.substr(0, pos);
			_buffer = receive.substr(pos + 2, std::string::npos);
			return result;
		}
	}
	std::string result = _buffer.substr(0, pos);
	_buffer = _buffer.substr(pos + 2, std::string::npos);
	return result;
}

bool Bot::connection_irc_ko()
{
	return _connection_irc_ko;
}

void Bot::authentication()
{
	send_to_irc("PASS " + _password_irc);
	send_to_irc("NICK " + _nickname);
	send_to_irc("USER " + _nickname + " 0 * :" + _nickname);

	std::string receive = get_next_msg();

	if (_connection_irc_ko || receive.find("001") == std::string::npos)
		throw (std::runtime_error(FG_RED"authentication failed" RESET));

	send_to_irc("JOIN #meteobot");
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
