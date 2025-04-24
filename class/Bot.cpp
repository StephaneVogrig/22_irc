/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:24:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 21:50:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* constructor ---------------------------------------------------------------*/

Bot::Bot(const std::string & ip, int port, const std::string & password_irc)
	:	_meteo(get_api_key()),
		_password_irc(password_irc),
		_nickname(BOT_NICKNAME),
		_channel_name("#" BOT_NICKNAME),
		_delimiter_irc("\r\n")
{
	log_(FG_PURPLE "Bot started " RESET + current_date_str() + FG_PURPLE " on ip " RESET + ip + FG_PURPLE " on port " RESET + to_string(port) +  FG_PURPLE " with password " RESET + password_irc);
	_socket_irc = create_socket();
	struct sockaddr_in addr_irc;
	addr_irc.sin_family = AF_INET;
	addr_irc.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &addr_irc.sin_addr) <= 0)
	{
		close(_socket_irc);
		throw (std::runtime_error("Bot: inet_pton failed"));
	}
	if (connect(_socket_irc, (struct sockaddr *)&addr_irc, sizeof(addr_irc)) < 0)
	{
		close(_socket_irc);
		throw (std::runtime_error( "Bot: connect failed: " + std::string(strerror(errno))));
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
	{
		Message msg(get_next_msg());
		std::string cmd = msg.get_command();
		if (cmd == "JOIN")
			rpl_to_join(msg);
		else if (cmd == "PRIVMSG")
			rpl_to_privmsg(msg);
		else if (cmd == "PING")
			rpl_to_ping(msg);
	}
}

void Bot::authentication()
{
	sigalarm_handler_setup();
	alarm(10);
	if (!_password_irc.empty())
		send_to_irc("PASS " + _password_irc);
	send_to_irc("NICK " + _nickname);
	send_to_irc("USER " + _nickname + " 0 * :" + _nickname);
	while (true)
	{
		Message msg(get_next_msg());
		const std::string & cmd = msg.get_command();
		if (cmd == "PING")
			rpl_to_ping(msg);
		else if (cmd == "433")
			throw (std::runtime_error("Authentication failed: nickname already in use"));
		else if (cmd == "451")
			throw (std::runtime_error("Authentication failed: not registered"));
		else if (cmd == "464")
			throw (std::runtime_error("Authentication failed: wrong password"));
		else if (cmd == "001")
		{
			log_(FG_PURPLE "Authentication successfull");
			break;
		}
	}
	send_to_irc("JOIN " + _channel_name);
	while (true)
	{
		Message msg(get_next_msg());
		const std::string & cmd(msg.get_command());
		if (cmd == "PING")
			rpl_to_ping(msg);
		else if (cmd == "JOIN")
		{
			log_(FG_PURPLE "join channel successfull");
			break;
		}
		else if (cmd == "403"
		|| cmd == "405"
		|| cmd == "475"
		|| cmd == "474"
		|| cmd == "471"
		|| cmd == "473"
		|| cmd == "476")
		{
			log_(FG_RED "join channel failed : " + cmd);
			break;
		}
	}
	alarm(0);
	sigalarm_handler_setdflt();
}

/* private utilities ---------------------------------------------------------*/

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

std::string Bot::get_next_msg()
{
	std::size_t pos = _buffer.find(_delimiter_irc);
	std::string result;
	while (pos == std::string::npos)
	{
		char temp[512];
		memset(temp, 0, sizeof(temp));
		int size_read = recv(_socket_irc, &temp, sizeof(temp), MSG_NOSIGNAL);

		// handle errors
		if (size_read == 0)
			throw (std::runtime_error("Server connection lost"));
		else if (size_read == -1)
		{
			check_sigint();
			throw std::runtime_error("get_next_msg: recv error: " RESET + std::string(strerror(errno)));
		}

		// handle data
		std::string receive(temp, size_read);
		pos = receive.find(_delimiter_irc);
		if (pos == std::string::npos)
			_buffer += receive;
		else
		{
			result = _buffer + receive.substr(0, pos);
			_buffer = receive.substr(pos + _delimiter_irc.length());
			log_(FG_YELLOW "<< " + result);
			return result;
		}
	}
	result += _buffer.substr(0, pos);
	_buffer = _buffer.substr(pos + _delimiter_irc.length());
	log_(FG_YELLOW "<< " + result);
	return result;
}

void Bot::send_meteo(const std::string & recipient, const std::string & location)
{
	try
	{
		if (location.empty())
		{
			send_privmsg(recipient, LOCATION_NOT_FOUND);
			return ;
		}

		std::string location_key = _meteo.get_location_key(location);
		if (location_key.empty())
		{
			send_privmsg(recipient, LOCATION_NOT_FOUND);
			return ;
		}
		else if (location_key == "Unauthorized")
		{
			send_privmsg(recipient, INVALID_API_KEY);
			return ;
		}

		WeatherInfo info = _meteo.fetch_current_conditions(location_key);
		if (info.description == "Unauthorized")
		{
			send_privmsg(recipient, INVALID_API_KEY);
			return ;
		}

		send_privmsg(recipient, "Weather for: " + location);
		send_privmsg(recipient, "Conditions : " + info.description);
		send_privmsg(recipient, "Temperature: " + info.temperature + "°C");
		send_privmsg(recipient, "Humidity   : " + info.humidity + "%");
		send_privmsg(recipient, "Pressure   : " + info.pressure + " mb");
		send_privmsg(recipient, "Visibility : " + info.visibility + " km");
		send_privmsg(recipient, "Wind       : " + info.wind_speed + " km/h from " + info.wind_direction);
		send_privmsg(recipient, "Wind gusts : " + info.wind_gust + " km/h");
		send_privmsg(recipient, "UV Index   : " + info.uv_index + " (" + info.uv_index_text + ")");
		send_privmsg(recipient, "Data provided by AccuWeather.com");
	}
	catch(const AccuWeatherAPI::Accu_error & e)
	{
		send_privmsg(recipient, e.what());
	}
}

void Bot::send_to_irc(const std::string & msg)
{
	log_(FG_GREEN ">> " + msg);
	std::string msg_irc = ":" + _nickname + " " + msg + _delimiter_irc;
	if (send(_socket_irc, msg_irc.c_str(), msg_irc.length(), MSG_NOSIGNAL) == -1)
	{
		check_sigint();
		throw std::runtime_error("send_to_irc: send error: " RESET + std::string(strerror(errno)));
	}
}

void Bot::send_privmsg(const std::string & recipient, const std::string & msg)
{
	send_to_irc("PRIVMSG " + recipient + " :" + msg);
}

void Bot::check_sigint()
{
	if (g_sigint)
		throw Close();
}

void Bot::rpl_to_ping(const Message & msg)
{
	std::string ball;
	if (msg.get_params().get_nbr() != 0)
		ball = msg.get_params().get_first();
	send_to_irc("PONG :" + ball);
}

void Bot::rpl_to_join(const Message & msg)
{
	send_privmsg(_channel_name, "Welcome to meteobot, " + msg.get_prefix() + ". Write the name of the city you want have the meteo");
}

void Bot::rpl_to_privmsg(const Message & msg)
{
	if (msg.get_params().get_nbr() == 0)
		return ;

	std::string recipient;
	if (msg.get_params().get_first() == _nickname)
		recipient = msg.get_prefix();
	else
		recipient = msg.get_params().get_first();

	if (msg.get_params().get_nbr() == 1 || msg.get_params().get_param(1).empty())
		send_privmsg(recipient, "I'm unable to work without destination");

	send_meteo(recipient, msg.get_params().get_param(1));
}

Bot::Close::Close() : std::exception()
{}
