/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:36 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/18 18:12:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <arpa/inet.h>
# include <exception>
# include <cerrno>
# include <cstring>
# include <string>
# include <poll.h>
# include <sys/socket.h>
# include "signal.hpp"

#include "socket.hpp"
#include "utils.hpp"
#include "Message.hpp"

#include <fstream>

#include "AccuWeatherAPI.hpp"

#define BOT_NICKNAME "meteobot"

class Bot
{
	public:

		Bot(int socket_irc, const std::string & password_irc);
		~Bot();

		void		run();
		void		send_to_irc(const std::string & msg);
		void		authentication();
		std::string	get_next_msg();
		bool		connection_irc_ko();
		void		receive_irc_data();
		void		process_irc_msg(const Message & msg);

	private:

		std::string	get_api_key();
		void		send_meteo(const std::string & location);

		AccuWeatherAPI _meteo;

		std::string	_buffer;
		int			_socket_irc;
		std::string _password_irc;
		bool		_connection_irc_ko;
		std::string	_nickname;

};

#endif
