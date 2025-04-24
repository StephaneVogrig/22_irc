/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:36 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 16:19:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <arpa/inet.h>
# include <cerrno>
# include <cstring>
# include <exception>
# include <fstream>
# include <string>
# include <sys/socket.h>

# include "AccuWeatherAPI.hpp"
# include "Message.hpp"

# include "log.hpp"
# include "signal.hpp"
# include "socket.hpp"
# include "utils.hpp"

# define BOT_NICKNAME "meteobot"
# define LOCATION_NOT_FOUND "Location not found"
# define INVALID_API_KEY "Invalid API key. Contact the administrator."

class Bot
{
	public:

		Bot(const std::string & ip, int port, const std::string & password_irc);
		~Bot();

		void		run();
		void		authentication();

	private:

		std::string	get_api_key();
		std::string	get_next_msg();
		void		process_irc_msg(const Message & msg);
		void		send_meteo(const std::string & recipient, const std::string & location);
		void		send_to_irc(const std::string & msg);
		void		send_privmsg(const std::string & recipient, const std::string & msg);
		void		check_sigint();

		AccuWeatherAPI _meteo;

		std::string	_buffer;
		int			_socket_irc;
		std::string _password_irc;
		std::string	_nickname;
		std::string	_channel_name;
		std::string	_delimiter_irc;

};

#endif
