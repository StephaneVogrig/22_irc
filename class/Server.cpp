/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 17:16:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "utils.hpp"

volatile sig_atomic_t	g_signal = 0;

/* constructor ---------------------------------------------------------------*/

Server::Server(int port, const std::string & password, const std::string & name)
		: _name(name), _port(port), _password(password), _nbr_connected(0)
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
	log_server(_fds[0].fd, "Closing server: " + to_string(_nbr_connected) + " client to close");
	for (int i = _nbr_connected; i > 0; --i)
	{
		if (send(_fds[i].fd, MSG_SERV_CLOSED, strlen(MSG_SERV_CLOSED), 0) == -1)
			throw(std::runtime_error("send failed"));
		close_connection(i);
	}
	close(_fds[0].fd);
	log_server(_fds[0].fd, BLINK_ON "SERVER CLOSED" BLINK_OFF);
	destroy_commands();
}

/* accessor ------------------------------------------------------------------*/

const std::string & Server::get_name() const
{
	return (_name);
}

const Client *Server::get_client_by_idx(int idx_in_array) const
{
	return _clients[idx_in_array] ;
}

Client * Server::get_client_by_name(const std::string & name)
{
	int i;
	for (i = get_nbr_connected(); i > 0; --i)
	{
		if (_clients[i]->get_nickname() == name)
			return (_clients[i]);
	}
	return NULL;
}

const std::string & Server::get_password(void) const
{
	return _password ;
}

int Server::get_nbr_connected(void)
{
	return _nbr_connected ;
}

Channel * Server::get_channel(const std::string & name)
{
	t_map_channel::iterator it = _channels.find(name);
	if (it == _channels.end())
		return NULL;
	return &(it->second) ;
}

/* exception -----------------------------------------------------------------*/

Server::Client_not_found::Client_not_found()
{}

/* public utilities ----------------------------------------------------------*/


void Server::run(void)
{
	log_server(_fds[0].fd, "Started server " RESET + current_date_str() + FG_YELLOW " on port " RESET + to_string(_port) +  FG_YELLOW " with password " RESET + _password);
	while (true)
	{
		info_waiting(true);
		int nbr_event = poll(_fds, _nbr_connected + 1, POLL_TIMEOUT_MS);
		if (g_signal)
			break ;
		if( nbr_event == -1)
			throw(std::runtime_error("poll failed"));
		if (nbr_event == 0)
		{
			for (int i = _nbr_connected; i > 0; --i)
				if (get_client_by_idx(i)->is_kicked())
					close_connection(i);
			continue ;
		}
		info_waiting(false);
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

void Server::create_channel(const std::string & name, const std::string & key)
{
	_channels.insert(std::make_pair(name, Channel(name, key)));
}

/* private utilities ---------------------------------------------------------*/

void Server::open_connection(int fd)
{
	_nbr_connected++;
	_fds[_nbr_connected].fd = fd;
	_fds[_nbr_connected].events = POLLIN;
	_clients[_nbr_connected] = new Client(fd);
	log_server(fd, "connection accepted");
}

void Server::close_connection(int i)
{
	int fd = _fds[i].fd;
	close(_fds[i].fd);
	_fds[i] = _fds[_nbr_connected];
	delete _clients[i];
	_clients[i] = _clients[_nbr_connected];
	_nbr_connected--;
	log_server(fd, "connection closed");
}

void Server::accept_connection()
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	int fd = accept(_fds[0].fd, (struct sockaddr *) &addr, &addr_len);
	if (fd == -1)
		throw(std::runtime_error("accept failed"));
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (_nbr_connected == NBR_CLIENT_MAX)
	{
		log_server(fd, "connection refused");
		if (send(fd, MSG_SERV_FULL, strlen(MSG_SERV_FULL), 0) == -1)
			throw(std::runtime_error("send failed"));
		close(fd);
		return ;
	}
	open_connection(fd);
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
	if (size_read <= 0 || get_client_by_idx(i)->is_kicked())
	{
		close_connection(i);
		return ;
	}
	std::string str_buffer(buffer);
	#if DEBUG
	std::cout 	<< FG_YELLOW "---- receive on fd [" RESET << _fds[i].fd
				<< FG_YELLOW "] ----" RESET << std::endl
				<< str_buffer << std::endl
				<< FG_YELLOW "------- end receive -------" RESET << std::endl;
	#endif
	receive_data(str_buffer, *(_clients[i]));
}

void Server::receive_data(const std::string & data, Client & client)
{
	std::string str = client.get_msg_buffer() + data;

	std::string delim("\r\n");
	size_t pos = str.find(delim);
	while (pos != std::string::npos)
	{
		std::string data_clean(str.substr(0, pos));
		log_msg(client.get_fd(), FG_YELLOW "<<", to_string(data_clean));
		Message msg(str.substr(0, pos));
		// log_msg(client.get_fd(), FG_RED "<<", to_string(msg));
		handle_msg(msg, client);
		if (client.is_kicked())
			return ;
		str.erase(0, pos + 2);
		pos = str.find(delim);
	}
	client.clear_msg_buffer();
	client.append_to_buffer(str);
}

void Server::init_commands(void)
{
	_commands["WHO"] = new Who();
	_commands["NICK"] = new Nick();
	_commands["USER"] = new User();
	_commands["PASS"] = new Pass();
	_commands["JOIN"] = new Join();
	_commands["PING"] = new Ping();
	_commands["PONG"] = new Pong();
	_commands["QUIT"] = new Quit();
	_commands["PART"] = new Part();
	_commands["KICK"] = new Kick();
	_commands["TOPIC"] = new Topic();
	_commands["INVITE"] = new Invite();
	_commands["PRIVMSG"] = new Privmsg();
	_commands["MODE"] = new Mode();
}

void Server::destroy_commands(void)
{
	for(std::map<std::string, Command *>::iterator it = _commands.begin();
		it != _commands.end(); ++it)
		delete (it->second);
}

void Server::handle_msg(const Message & msg, Client & client)
{
	try
	{
		Command * cmd_ptr = _commands[msg.get_command()];
		if (!cmd_ptr)
			ERR_421_UNKNOWNCOMMAND(client, msg.get_command());

		if (!client.is_registed() && !is_cmd_to_register(*cmd_ptr))
			ERR_451_NOTREGISTERED(client, *this);

		cmd_ptr->exec(client, msg.get_params(), *this);
	}
	catch(const Protocole_error & e)
	{}
}

void Server::info_waiting(bool state)
{
	static int waiting_state;

	if (state == false)
	{
		waiting_state = 0;
		return ;
	}

	if (waiting_state == 0)
	{
		std::cout	<< "\r" ERASE_LINE FG_GREEN << _nbr_connected << " client connected - serveur waiting";
		std::cout.flush();
	}
	else
	{
		std::cout << FG_WHITE << "." ;
		std::cout.flush();
	}
	waiting_state++;
	if (waiting_state == 10)
		waiting_state = 0;
}

void Server::remove_client_from_channel(Client & client, Channel & channel)
{
	t_map_channel::iterator it = _channels.find(channel.get_name());
	channel.remove_client(client);
	log("client in channel : " + to_string(channel.get_nbr_client()));
	if (channel.get_nbr_client() == 0)
	{
		log("erase channel : " + to_string(it->second.get_name()));
		_channels.erase(it);
	}
}

void Server::quit_all_serv_channels(Client & client, const std::string & msg)
{
	for(t_map_channel::iterator it = _channels.begin();
		it != _channels.end(); ++it)
	{
		if (it->second.is_join(client))
		{
			it->second.send_quit(client, msg);
			remove_client_from_channel(client, it->second);
		}
	}
}

bool Server::is_cmd_to_register(const Command & cmd) const
{
	const std::string & cmd_name = cmd.get_name();
	return cmd_name == "PASS" || cmd_name == "NICK" || cmd_name == "USER" || cmd_name == "QUIT";
}
