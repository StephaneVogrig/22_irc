/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/14 16:21:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <errno.h>
# include <fcntl.h>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdio.h>
# include <string.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>

# include "Client.hpp"
# include "ServerException.hpp"

# include "utils.hpp"
# include "signal.h"

# define BACKLOG 20
# define POLL_TIMEOUT 2000
# define CLIENT_BUFFER_SIZE 256
# define NBR_CLIENT_MAX 1

# define MSG_WELCOME "Welcome on the best irc server\n"
# define MSG_SERV_FULL "Connection refused : server full\n"
# define MSG_SERV_CLOSED "Server closed\n"

typedef struct pollfd t_pollfd;

extern volatile sig_atomic_t	g_signal;

class Server
{
	public:

		Server(int port, const std::string & password);
		~Server(void);

		void run(void);

	private:

		Client *			_clients[NBR_CLIENT_MAX];

		const int			_port;
		const std::string	_password;
		int					_nbr_connected;
		t_pollfd			_fds[NBR_CLIENT_MAX];

		void handleEvent(void);
		void acceptConnection(void);
		void handleClientMsg(int i);
		void closeConnection(int i);
		void openConnection(int fd);
};

#endif