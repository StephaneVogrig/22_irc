/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:36 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/19 15:19:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <arpa/inet.h>
# include <exception>
# include <cerrno>
# include <cstring>
# include <string>
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
		void		authentication();

	private:

		void		receive_irc_data();
		std::string	get_next_msg();
		void		process_irc_msg(const Message & msg);
		void		send_meteo(const std::string & location);
		void		send_to_irc(const std::string & msg);
		void		sent_privmsg(const std::string & msg);
		std::string	get_api_key();
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
