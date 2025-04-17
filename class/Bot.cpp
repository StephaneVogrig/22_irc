/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:24:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/17 00:30:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* constructor ---------------------------------------------------------------*/

Bot::Bot(int port, const std::string & password_irc)
	:	_password_irc(password_irc),
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

void Bot::run()
{
	struct pollfd pollfds[1];
	pollfds[0].fd = _socket_irc;
	pollfds[0].events = POLLIN;
	AccuWeatherAPI meteo("papFcEEYGbeI8wKArs5dVLz22wSAZ2A1");

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
		if (receive.find("!meteo"))
			WeatherInfo info = meteo.fetch_current_conditions(meteo.get_location_key("Paris"));
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
