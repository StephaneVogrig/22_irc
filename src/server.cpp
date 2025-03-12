/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 20:29:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int create_server(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw(std::runtime_error(RED "socket init failed" RESET));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		perror("");
		throw(ServerException("bind failed", sock));
	}
	if (listen(sock, BACKLOG) == -1)
		throw(ServerException("listen failed", sock));
	std::cout	<< BLUE "create server " RESET << sock
				<< BLUE " on port " RESET << port << std::endl;
	return (sock);
}

void accept_connection(t_pollfd *fds, nfds_t * nbr_fd)
{
	std::cout << "accept connection " << std::endl;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);

	int fd = accept((*fds).fd, (struct sockaddr *) &addr, &addr_len);
	if (fd == -1)
		throw(ServerException("accept failed", (*fds).fd));
	fds[*nbr_fd].fd = fd;
	fds[*nbr_fd].events = POLLIN;
	(*nbr_fd)++;
	if (send(fd, "bonjour", strlen("bonjour"), 0) == -1)
		throw(ServerException("send failed", (*fds).fd));
}

void handle_client_msg(t_pollfd *fds, int pos, nfds_t * nbr_fd)
{
	std::cout << "handle_client_msg " << std::endl;
	char buffer[CLIENT_BUFFER_SIZE];
	int size_read = recv(fds[pos].fd, buffer, CLIENT_BUFFER_SIZE - 1, 0);
	if (size_read <= 0)
	{
		close(fds[pos].fd);
		(*nbr_fd)--;
		fds[pos] = fds[*nbr_fd];
		std::cout << "client connection close " << fds[pos].fd << std::endl;
	}
	buffer[size_read] = '\0';
	std::cout << buffer << std::endl;
}

void handle_event(const int server, t_pollfd *fds, nfds_t * nbr_fd)
{
	(void) server;
	std::cout << "incoming connection " << (*fds).events << std::endl;
	if (fds[0].revents & POLLIN)
		accept_connection(fds, nbr_fd);
	for (nfds_t i = 1; i < *nbr_fd; ++i)
	{
		if (fds[i].revents & POLLIN)
			handle_client_msg(fds, i, nbr_fd);
	}
}

void run_server(const int server, const int port, const std::string & password)
{
	std::cout	<< BLUE "run server " RESET << server
				<< BLUE " on port " RESET << port
				<< BLUE " with password " RESET << password << std::endl;

	t_pollfd fds[POLL_NBR_CLIENT + 1];
	memset(fds, 0, sizeof(fds));
	(*fds).fd = server;
	(*fds).events = POLLIN;
	nfds_t nbr_fd = 1;

	while (true)
	{
		int nbr_event = poll(fds, nbr_fd, POLL_TIMEOUT);
		if( nbr_event == -1)
			throw(ServerException("poll failed", server));
		if (nbr_event == 0)
		{
			std::cout << "serveur waiting..." << std::endl;
			continue ;
		}
		handle_event(server, fds, &nbr_fd);
	}
}
