/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/01 16:05:39 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <exception>

# include "signal.h"

# include "socket.hpp"
# include <poll.h>

# include "utils.hpp"

# include "Channel.hpp"
# include "Client.hpp"
# include "Message.hpp"

# include "log.hpp"

# include "Command.hpp"
# include "Nick.hpp"
# include "User.hpp"
# include "Pass.hpp"
# include "Join.hpp"
# include "Ping.hpp"
# include "Pong.hpp"
# include "Topic.hpp"
# include "Quit.hpp"
# include "Part.hpp"
# include "Kick.hpp"
# include "Invite.hpp"
# include "Privmsg.hpp"
# include "Protocole_error.hpp"

# include "settings.hpp"

# define MSG_WELCOME "Welcome on the best irc server\n"
# define MSG_SERV_FULL "Connection refused : server full\n"
# define MSG_SERV_CLOSED "Server closed\n"

// # define DEBUG

typedef struct pollfd t_pollfd;
typedef std::map<std::string, Channel> t_map_channel;

extern volatile sig_atomic_t	g_signal;

class Server
{
	public:

		Server(int port, const std::string & password, const std::string & name);
		~Server();

		const std::string &	get_name() const;
		const Client *		get_client(int idx_in_array) const;
		const std::string &	get_password() const;
		int					get_nbr_connected() const;
		Client &			get_client_r(const std::string & name);
		Channel *			get_channel(const std::string & name);
		void				close_connection(int i);

		class Channel_not_found : std::exception
		{
			public:
				Channel_not_found();
		};
		class Client_not_found : std::exception
		{
			public:
				Client_not_found();
		};

		void run(void);
		bool channel_exist(const std::string & name);
		void create_channel(const std::string & name);
		void info_waiting(bool state);

	private:

		std::string							_name;
		const int							_port;
		const std::string					_password;
		int									_nbr_connected;
		t_pollfd							_fds[NBR_CLIENT_MAX];
		Client *							_clients[NBR_CLIENT_MAX];
		std::map<std::string, Command *>	_commands;
		t_map_channel						_channels;

		void open_connection(int fd);
		void accept_connection();

		void handle_event();
		void handle_client_data(int i);
		void receive_data(const std::string & data, Client & client);

		void init_commands();
		void destroy_commands();
		void handle_msg(const Message & msg, Client & client);

};

#endif