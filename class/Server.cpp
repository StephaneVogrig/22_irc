/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/25 15:14:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

volatile sig_atomic_t	g_signal = 0;

/* constructor ---------------------------------------------------------------*/

Server::Server(int port, const std::string & password)
		: _port(port), _password(password), _nbr_connected(0)
{
	memset(_fds, 0, sizeof(_fds));
	_fds[0].fd = create_socket();
	_fds[0].events = POLLIN;
	bind_socket(_fds[0].fd, port);
	if (listen(_fds[0].fd, BACKLOG) == -1)
		throw(std::runtime_error("listen failed"));
	init_commands();
}

/* destructor ----------------------------------------------------------------*/

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
	destroy_commands();
}

/* accessor ------------------------------------------------------------------*/

const Client *Server::get_client(int idx_in_array) const
{
	return _clients[idx_in_array] ;
}

const std::string &Server::get_password(void) const
{
	return _password ;
}

int Server::get_nbr_connected(void) const
{
	return _nbr_connected ;
}

Channel & Server::get_channel(const std::string & name)
{
	t_map_channel::iterator it = _channels.find(name);
	return it->second ;
}

/* public utilities ----------------------------------------------------------*/

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
			for (int i = _nbr_connected; i > 0; --i)
				if (get_client(i)->is_kicked())
					close_connection(i);
			continue ;
		}
		handle_event();
	}
}

bool Server::channel_exist(const std::string & name)
{
	t_map_channel::iterator it = _channels.find(name);
	if (it == _channels.end())
		return false ;
	return true ;
}

void Server::create_channel(const std::string & name)
{
	_channels.insert(std::make_pair(name, Channel(name)));
}

/* private utilities ---------------------------------------------------------*/

void Server::open_connection(int fd)
{
	_nbr_connected++;
	_fds[_nbr_connected].fd = fd;
	_fds[_nbr_connected].events = POLLIN;
	_clients[_nbr_connected] = new Client(fd);
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

void Server::handle_event(void)
{
	int imax = _nbr_connected;
	if (_fds[0].revents & POLLIN)
		accept_connection();
	for (int i = imax; i > 0; --i)
	{
		if (_fds[i].revents & POLLIN)
			handle_client_data(i);
	}
}

void Server::handle_client_data(int i)
{
	char buffer[CLIENT_BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));
	int size_read = recv(_fds[i].fd, buffer, CLIENT_BUFFER_SIZE - 1, 0);
	if (size_read <= 0 || get_client(i)->is_kicked())
	{
		close_connection(i);
		return ;
	}
	std::string str_buffer(buffer);
	std::cout 	<< YELLOW "---- receive on fd [" RESET << _fds[i].fd
				<< YELLOW "] ----" RESET << std::endl
				<< str_buffer << std::endl
				<< YELLOW "------- end receive -------" RESET << std::endl;
	receive_data(str_buffer, _clients[i]);
}

void Server::receive_data(const std::string & data, Client * client)
{
	std::string str = client->get_msg_buffer() + data;

	std::string delim("\r\n");
	size_t pos = str.find(delim);
	while (pos != std::string::npos)
	{
		std::string msg = str.substr(0, pos);
		std::cout	<<  PURPLE "["  RESET << client->get_fd() << PURPLE "] : "  RESET
					<< msg << std::endl;
		handle_msg(msg, client);
		if (client->is_kicked())
			return ;
		str.erase(0, pos + 2);
		pos = str.find(delim);
	}
	client->clear_msg_buffer();
	client->append_to_buffer(str);
}

void Server::init_commands(void)
{
	_commands["NICK"] = new Nick();
	_commands["USER"] = new User();
	_commands["PASS"] = new Pass();
	_commands["JOIN"] = new Join();
	_commands["PING"] = new Ping();
	_commands["PONG"] = new Pong();
	_commands["QUIT"] = new Quit();
}

void Server::destroy_commands(void)
{
	for(std::map<std::string, Command *>::iterator it = _commands.begin();
		it != _commands.end(); ++it)
		delete (it->second);
}
void Server::handle_msg(const std::string str, Client * client)
{
	int pos = str.find(' ');
	std::string cmd = str.substr(0, pos);
	std::string param = str.substr(pos + 1, str.length());
	for(std::string::iterator it = cmd.begin(); it <= cmd.end(); ++it)
		*it = std::toupper(*it);
	Command * cmd_ptr = _commands[cmd];
	if (cmd_ptr)
		cmd_ptr->exec(client, param, *this);
	else
		std::cout << "command not found" << std::endl;
}
