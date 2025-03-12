/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 15:46:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.hpp"
#include "ServerException.hpp"

#define BACKLOG 20

int create_server(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (sock == -1)
		throw(std::runtime_error(RED "socket init failed" RESET));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; /* address family: AF_INET */
	addr.sin_port = htons(port);   /* port in network byte order */
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		throw(ServerException(RED "bind failed" RESET, sock));
	if (listen(sock, BACKLOG) == -1)
		throw(ServerException(RED "listen failed" RESET, sock));
	std::cout	<< BLUE "create server on port " RESET << port << std::endl;
	return (sock);
}

void run_server(const int server, const int port, const std::string & password)
{
	std::cout	<< BLUE "run server " RESET << server
				<< BLUE " on port " RESET << port
				<< BLUE " with password " RESET << password << std::endl;
}
