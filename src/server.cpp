/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 18:22:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.hpp"
#include "ServerException.hpp"
#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>

#define BACKLOG 20
#define POLL_TIMEOUT 2000
#define POLL_NBR_CLIENT 10

int create_server(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw(std::runtime_error(RED "socket init failed" RESET));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; /* address family: AF_INET */
	addr.sin_port = htons(port);   /* port in network byte order */
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		throw(ServerException("bind failed", sock));
	if (listen(sock, BACKLOG) == -1)
		throw(ServerException("listen failed", sock));
	std::cout	<< BLUE "create server " RESET << sock
				<< BLUE " on port " RESET << port << std::endl;
	return (sock);
}

void run_server(const int server, const int port, const std::string & password)
{
	std::cout	<< BLUE "run server " RESET << server
				<< BLUE " on port " RESET << port
				<< BLUE " with password " RESET << password << std::endl;

	struct pollfd fds[POLL_NBR_CLIENT + 1];
	memset(fds, 0, sizeof(fds));
	(*fds).fd = server;
	(*fds).events = POLLIN;
	nfds_t nbr_fd = 1;

	while (true)
	{
		if(poll(fds, nbr_fd, POLL_TIMEOUT) == -1)
			throw(ServerException("poll failed", server));
		std::cout << "connection entrante " << std::endl;
	}
}
