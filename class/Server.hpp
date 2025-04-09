/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/09 18:06:01 by svogrig          ###   ########.fr       */
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
# include "Who.hpp"
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
# include "Mode.hpp"
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
		Client *			get_client_by_name(const std::string & name);
		const std::string &	get_password() const;
		int					get_nbr_connected();
		Channel *			get_channel(const std::string & name);

		class Client_not_found : std::exception
		{
			public:
				Client_not_found();
		};

		void run(void);
		void close_connection(Client & client);
		bool channel_exist(const std::string & name);
		void create_channel(const std::string & name, const std::string & key);
		void info_waiting(bool state);
		void remove_client_from_channel(Client & client, Channel & channel);
		void quit_all_serv_channels(Client & client, const std::string & msg);

	private:

		std::string							_name;
		const int							_port;
		const std::string					_password;
		int									_nbr_connected;
		t_pollfd							_fds[NBR_CLIENT_MAX];

		typedef std::map < int, Client * >	t_clients;
		t_clients							_clients_map;

		std::map<std::string, Command *>	_commands;
		t_map_channel						_channels;

		void open_connection(int fd);
		void accept_connection();
		void close_connection(int i);

		void handle_event();
		void handle_client_data(Client & client);
		void receive_data(const std::string & data, Client & client);
		void handle_msg(const Message & msg, Client & client);

		void init_commands();
		void destroy_commands();
		bool is_cmd_to_register(const Command & cmd) const;

		bool client_exist(Client * client_ptr);

};

#endif
