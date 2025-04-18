/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:24:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/17 23:54:39 by svogrig          ###   ########.fr       */
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
	std::string msg = "PRIVMSG #meteobot :Meteo for " + location + ": " + info.description + ", " + info.temperature + "°C";
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
		std::string receive = get_next_msg();
		std::cout << receive << std::endl;
		size_t pos = receive.find("!meteo");
		if (pos != std::string::npos)
		{
			std::cout << FG_GREEN "Meteo command received" RESET << std::endl;
			if (receive.length() < pos + 7)
			{
				send_to_irc("PRIVMSG #meteobot :Location not found");
				std::cout << FG_RED "Location not found" RESET << std::endl;
				continue ;
			}
			std::string location = receive.substr(pos + 7, std::string::npos);
			if (!location.empty())
				send_meteo(location);
		}
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
