/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/14 14:41:33 by svogrig          ###   ########.fr       */
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
# include "ServerException.hpp"
# include "utils.hpp"
# include "signal.h"

# define BACKLOG 20
# define POLL_TIMEOUT 2000
# define POLL_NBR_CLIENT 10
# define CLIENT_BUFFER_SIZE 256

typedef struct pollfd t_pollfd;

extern volatile sig_atomic_t	g_signal;

class Server
{
	public:

		Server(int port, const std::string & password);
		~Server(void);

		void run(void);

	private:

		const int			_port;
		const std::string	_password;
		int					_nbr_connected;
		t_pollfd			_fds[POLL_NBR_CLIENT + 1];

		void handle_event(void);
		void accept_connection(void);
		void handle_client_msg(int i);

};

#endif