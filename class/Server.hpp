/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 19:22:27 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <csignal>
# include <exception>
# include <iostream>
# include <map>
# include <string>

# include <poll.h>

# include "log.hpp"
# include "reply.hpp"
# include "settings.hpp"
# include "socket.hpp"
# include "utils.hpp"

# include "Channel.hpp"
# include "Client.hpp"
# include "Message.hpp"
# include "Protocole_error.hpp"

# include "Command.hpp"
# include "Who.hpp"
# include "Nick.hpp"
# include "User.hpp"
# include "Pass.hpp"
# include "Join.hpp"
# include "Ping.hpp"
# include "Topic.hpp"
# include "Quit.hpp"
# include "Part.hpp"
# include "Kick.hpp"
# include "Mode.hpp"
# include "Invite.hpp"
# include "Privmsg.hpp"
# include "Notice.hpp"
# include "List.hpp"

# define DELIM_IRC "\r\n"

typedef struct pollfd t_pollfd;

class Server
{
	public:

		Server(int port, const std::string & password, const std::string & name);
		~Server();

		const std::string &	get_name() const;
		Client *			get_client_by_name(const std::string & name);
		const std::string &	get_password() const;
		const std::string &	get_creation_date_time() const;
		const std::string &	get_verstion() const;
		int					get_nbr_connected();
		Channel *			get_channel(const std::string & name);

		void run(void);
		void rpl_accept(Client & client);
		void close_connection(Client & client);

		bool channel_exist(const std::string & name);
		void create_channel(const std::string & name, const std::string & key);
		void remove_client_from_channel(Client & client, Channel & channel);
		void quit_all_serv_channels(Client & client, const std::string & msg);
		void send_channel_list(Client & client);

	private:

		std::string			_name;
		const int			_port;
		const std::string	_password;
		const std::string	_creation_date_time;
		const std::string	_version;
		int					_nbr_connected;
		t_pollfd			_pollfds[NBR_CLIENT_MAX];

		typedef std::map < int, Client * >	t_clients_serv;
		t_clients_serv		_serv_clients;

		typedef std::map<std::string, Command *> t_commands;
		t_commands			_commands;

		typedef std::map<std::string, Channel> t_channels;
		t_channels			_channels;

		void init_commands();
		void destroy_commands();
		bool is_cmd_to_register(const Command & cmd) const;

		void accept_connection();
		void close_connection(int i);

		void handle_event();
		void handle_client_data(Client & client);
		void receive_data(const std::string & data, Client & client);
		void handle_msg(const Message & msg, Client & client);

		bool client_exist(const Client & client_ptr) const;

		void info_waiting(bool state);

};

#endif
