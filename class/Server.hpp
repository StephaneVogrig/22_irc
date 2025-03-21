/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/22 11:22:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <poll.h>

# include "signal.h"
# include "socket.hpp"
# include "utils.hpp"

# include "Channel.hpp"
# include "Client.hpp"

# include "Command.hpp"
# include "Nick.hpp"
# include "User.hpp"
# include "Pass.hpp"
# include "Join.hpp"

# define BACKLOG 20
# define POLL_TIMEOUT 2000
# define CLIENT_BUFFER_SIZE 256
# define NBR_CLIENT_MAX 2

# define MSG_WELCOME "Welcome on the best irc server\n"
# define MSG_SERV_FULL "Connection refused : server full\n"
# define MSG_SERV_CLOSED "Server closed\n"

typedef struct pollfd t_pollfd;
typedef std::map<std::string, Channel> t_map_channel;

extern volatile sig_atomic_t	g_signal;

class Server
{
	public:

		Server(int port, const std::string & password);
		~Server(void);

		const Client *		get_client(int idx_in_array) const;
		const std::string &	get_password(void) const;
		int					get_nbr_connected(void) const;
		Channel &			get_channel(const std::string & name);

		void run(void);
		bool channel_exist(const std::string & name);
		void create_channel(const std::string & name);

	private:

		const int							_port;
		const std::string					_password;
		int									_nbr_connected;
		t_pollfd							_fds[NBR_CLIENT_MAX];
		Client *							_clients[NBR_CLIENT_MAX];
		std::map<std::string, Command *>	_commands;
		t_map_channel						_channels;

		void open_connection(int fd);
		void accept_connection(void);
		void close_connection(int i);

		void handle_event(void);
		void handle_client_data(int i);
		void receive_data(const std::string & data, Client * client);

		void init_commands(void);
		void destroy_commands(void);
		void handle_cmd(const std::string str, Client * client);

};

#endif