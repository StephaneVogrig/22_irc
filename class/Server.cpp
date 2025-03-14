/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/14 19:05:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

volatile sig_atomic_t	g_signal = 0;

static int create_socket(void)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw(std::runtime_error("socket failed"));
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		close(sock);
		throw(std::runtime_error("setsockoptit  failed"));
	}
	return sock;
}

static void bind_socket(int sock, int port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		perror("");
		throw(std::runtime_error("bind failed"));
	}
}

Server::Server(int port, const std::string & password)
		: _port(port), _password(password), _nbr_connected(0)
{
	memset(_fds, 0, sizeof(_fds));
	_fds[0].fd = create_socket();
	_fds[0].events = POLLIN;
	bind_socket(_fds[0].fd, port);
	if (listen(_fds[0].fd, BACKLOG) == -1)
		throw(std::runtime_error("listen failed"));
}

Server::~Server(void)
{
	std::cout <<  PURPLE "Closing server " RESET << _nbr_connected <<  PURPLE " client to close" RESET << std::endl;
	for (int i = _nbr_connected; i > 0; --i)
	{
		if (send(_fds[i].fd, MSG_SERV_CLOSED, strlen(MSG_SERV_CLOSED), 0) == -1)
			throw(std::runtime_error("send failed"));
		close_connection(i);
	}
	close(_fds[0].fd);
	std::cout << PURPLE_BLINK "SERVER CLOSED" RESET << std::endl;
}

void Server::run(void)
{
	std::cout	<< PURPLE "run server " RESET << _fds[0].fd
				<< PURPLE " on port " RESET << _port
				<< PURPLE " with password " RESET << _password << std::endl;
	while (true)
	{
		int nbr_event = poll(_fds, _nbr_connected + 1, POLL_TIMEOUT);
		if (g_signal)
			break ;
		if( nbr_event == -1)
			throw(std::runtime_error("poll failed"));
		if (nbr_event == 0)
		{
			std::cout	<< GREY "serveur waiting... "
						<< _nbr_connected << " client connected" RESET << std::endl;
			continue ;
		}
		handle_event();
	}
}

void Server::handle_event(void)
{
	int imax = _nbr_connected;
	if (_fds[0].revents & POLLIN)
		accept_connection();
	for (int i = imax; i > 0; --i)
	{
		if (_fds[i].revents & POLLIN)
			handle_client_msg(i);
	}
}

void Server::accept_connection()
{
	std::cout << PURPLE "asking connection : " RESET ;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	int fd = accept(_fds[0].fd, (struct sockaddr *) &addr, &addr_len);
	if (fd == -1)
		throw(std::runtime_error("accept failed"));
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (_nbr_connected == NBR_CLIENT_MAX)
	{
		std::cout << PURPLE "refused, server full" RESET << std::endl;
		if (send(fd, MSG_SERV_FULL, strlen(MSG_SERV_FULL), 0) == -1)
			throw(std::runtime_error("send failed"));
		close(fd);
		return ;
	}
	open_connection(fd);
	std::cout << PURPLE "accept connection on fd " RESET << fd << std::endl;
	if (send(fd, MSG_WELCOME, strlen(MSG_WELCOME), 0) == -1)
		throw(std::runtime_error("send failed"));
}

void Server::handle_client_msg(int i)
{
	char buffer[CLIENT_BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));
	int size_read = recv(_fds[i].fd, buffer, CLIENT_BUFFER_SIZE - 1, 0);
	if (size_read <= 0)
	{
		close_connection(i);
		return ;
	}
	std::string str(buffer);
	_clients[i]->append_to_buffer(str);
	std::string target("\r\n");
	size_t pos = str.find(target);
	if (pos != std::string::npos)
	{
		std::cout	<<  PURPLE "["  RESET << _fds[i].fd << PURPLE "] : "  RESET
					<< _clients[i]->get_msg_buffer() << std::endl;
		_clients[i]->clear_msg_buffer();
	}
}

void Server::open_connection(int fd)
{
	_nbr_connected++;
	_fds[_nbr_connected].fd = fd;
	_fds[_nbr_connected].events = POLLIN;
	_clients[_nbr_connected] = new Client();
}

void Server::close_connection(int i)
{
	int fd = _fds[i].fd;
	close(_fds[i].fd);
	_fds[i] = _fds[_nbr_connected];
	delete _clients[i];
	_clients[i] = _clients[_nbr_connected];
	_nbr_connected--;
	std::cout << PURPLE "client connection close " RESET << fd << std::endl;
}
