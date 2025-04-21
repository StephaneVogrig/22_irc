/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 20:26:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "signal.hpp"
#include "utils.hpp"

/* constructor ---------------------------------------------------------------*/

Server::Server(int port, const std::string & password, const std::string & name)
		: _name(name), _port(port), _password(password), _nbr_connected(0)
{
	memset(_pollfds, 0, sizeof(_pollfds));
	_pollfds[0].fd = create_socket();
	_pollfds[0].events = POLLIN;
	bind_socket(_pollfds[0].fd, port);
	if (listen(_pollfds[0].fd, BACKLOG) == -1)
	{
		close(_pollfds[0].fd);
		throw(std::runtime_error("Server: listen failed"));
	}
	init_commands();
}

/* destructor ----------------------------------------------------------------*/

Server::~Server(void)
{
	log_server(_pollfds[0].fd, "Closing server: " + to_string(_nbr_connected) + " client to close");
	for (int i = _nbr_connected; i > 0; --i)
	{
		std::string msg("Server closed" DELIM_IRC);
		if (send(_pollfds[i].fd, msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1)
			throw(std::runtime_error("~Server: send failed"));
		close_connection(i);
	}
	close(_pollfds[0].fd);
	log_server(_pollfds[0].fd, BLINK_ON "SERVER CLOSED" BLINK_OFF);
	destroy_commands();
}

/* accessor ------------------------------------------------------------------*/

const std::string & Server::get_name() const
{
	return (_name);
}

Client * Server::get_client_by_name(const std::string & name)
{
	for (t_clients_serv::iterator it = _serv_clients.begin(); it != _serv_clients.end(); ++it)
	{
		if (it->second->get_nickname() == name)
			return it->second;
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
	t_channels::iterator it = _channels.find(name);
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
	log_server(_pollfds[0].fd, "Started server " RESET + current_date_str() + FG_YELLOW " on port " RESET + to_string(_port) +  FG_YELLOW " with password " RESET + _password);
	while (true)
	{
		info_waiting(true);
		int nbr_event = poll(_pollfds, _nbr_connected + 1, POLL_TIMEOUT_MS);
		if (g_sigint)
			break ;
		if( nbr_event == -1)
			throw(std::runtime_error("poll failed" + std::string(strerror(errno))));
		if (nbr_event == 0)
			continue ;
		info_waiting(false);
		handle_event();
	}
}

bool Server::channel_exist(const std::string & name)
{
	t_channels::iterator it = _channels.find(name);
	if (it == _channels.end())
		return false ;
	return true ;
}

void Server::create_channel(const std::string & name, const std::string & key)
{
	_channels.insert(std::make_pair(name, Channel(name, key)));
}

/* private utilities ---------------------------------------------------------*/

void Server::init_commands(void)
{
	_commands["WHO"] = new Who();
	_commands["NICK"] = new Nick();
	_commands["USER"] = new User();
	_commands["PASS"] = new Pass();
	_commands["JOIN"] = new Join();
	_commands["PING"] = new Ping();
	_commands["QUIT"] = new Quit();
	_commands["PART"] = new Part();
	_commands["KICK"] = new Kick();
	_commands["TOPIC"] = new Topic();
	_commands["INVITE"] = new Invite();
	_commands["PRIVMSG"] = new Privmsg();
	_commands["MODE"] = new Mode();
	_commands["NOTICE"] = new Notice();
}

void Server::destroy_commands(void)
{
	for(std::map<std::string, Command *>::iterator it = _commands.begin();
		it != _commands.end(); ++it)
		delete (it->second);
}

bool Server::is_cmd_to_register(const Command & cmd) const
{
	const std::string & cmd_name = cmd.get_name();
	return cmd_name == "PASS" || cmd_name == "NICK" || cmd_name == "USER" || cmd_name == "QUIT";
}

void Server::accept_connection()
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);

	int fd = accept(_pollfds[0].fd, (struct sockaddr *) &addr, &addr_len);
	if (fd == -1)
		throw(std::runtime_error("accept failed"));

	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (_nbr_connected == NBR_CLIENT_MAX)
	{
		std::string msg("Connection refused : server full");
		log_server(fd, msg);
		msg += DELIM_IRC;
		if (send(fd, msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1)
			throw(std::runtime_error("send failed in accept connection"));
		close(fd);
		return ;
	}

	_nbr_connected++;
	_pollfds[_nbr_connected].fd = fd;
	_pollfds[_nbr_connected].events = POLLIN;
	_serv_clients[fd] = new Client(fd, addr);
	log_server(fd, "connection accepted");
}

void Server::close_connection(Client & client)
{
	for (t_channels::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		it->second.remove_from_invited(client);
	}

	for (int i = 1; i <=_nbr_connected; ++i)
	{
		if (_pollfds[i].fd == client.get_fd())
		{
			close_connection(i);
			return ;
		}
	}
}

void Server::close_connection(int i)
{
	int fd = _pollfds[i].fd;
	close(fd);
	_pollfds[i] = _pollfds[_nbr_connected--];
	t_clients_serv::iterator it = _serv_clients.find(fd);
	delete it->second;
	_serv_clients.erase(it);
	log_server(fd, "connection closed");
}

void Server::handle_event(void)
{
	int imax = _nbr_connected;
	if (_pollfds[0].revents & POLLIN)
		accept_connection();
	for (int i = imax; i > 0; --i)
	{
		Client * client = _serv_clients.find(_pollfds[i].fd)->second;
		if (_pollfds[i].revents & POLLIN)
		{
			handle_client_data(*client);
		}
		else if (_pollfds[i].revents & (POLLHUP | POLLNVAL))
		{
			close_connection(*client);
		}
	}
}

void Server::handle_client_data(Client & client)
{
	char buffer[CLIENT_BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));
	int size_read = recv(client.get_fd(), buffer, CLIENT_BUFFER_SIZE - 1, 0);
	if (size_read <= 0)
	{
		client.quit_quit_all_channels(*this, "QUIT :Connection lost");
		close_connection(client);
		return ;
	}
	std::string str_buffer(buffer);
	receive_data(str_buffer, client);
}

void Server::receive_data(const std::string & data, Client & client)
{
	std::string str = client.get_msg_buffer() + data;
	size_t pos = str.find(DELIM_IRC);
	while (pos != std::string::npos)
	{
		std::string msg(str.substr(0, pos));
		log_msg(client.get_fd(), FG_YELLOW "<<", msg);
		handle_msg(Message(msg), client);
		if (!client_exist(client))
			return ;
		str.erase(0, pos + 2);
		pos = str.find(DELIM_IRC);
	}
	client.clear_msg_buffer();
	client.append_to_buffer(str);
}

void Server::handle_msg(const Message & msg, Client & client)
{
	try
	{
		Command * cmd_ptr = _commands[msg.get_command()];
		if (!cmd_ptr)
			ERR_421_UNKNOWNCOMMAND(client, msg.get_command(), *this);

		if (!client.is_registed() && !is_cmd_to_register(*cmd_ptr))
			ERR_451_NOTREGISTERED(client, *this);

		cmd_ptr->exec(client, msg.get_params(), *this);
	}
	catch(const Protocole_error & e)
	{}
}

bool Server::client_exist(const Client & client) const
{
	for (t_clients_serv::const_iterator it = _serv_clients.begin(); it != _serv_clients.end(); ++it)
	{
		if (it->second == &client)
			return true;
	}
	return false;
}

void Server::info_waiting(bool waiting)
{
	static int waiting_state;

	if (waiting == false)
	{
		std::cout << "\r" ERASE_LINE FG_GREEN;
		std::cout.flush();
		return ;
	}
	clock_t t = clock() / 500;
	int state = t % 4;
	if (state != waiting_state)
	{
		std::cout << "\r" ERASE_LINE FG_GREEN " " << _nbr_connected << " client connected - serveur waiting";
		for (int i = 1; i <= state; ++i)
				std::cout << ".";
		std::cout << "\r";
		std::cout.flush();
		waiting_state = state;
	}
}

void Server::remove_client_from_channel(Client & client, Channel & channel)
{
	t_channels::iterator it = _channels.find(channel.get_name());
	channel.remove_client(client);

	if (channel.get_nbr_client() == 0)
	{
		channel.log("destroyed");
		_channels.erase(it);
		return ;
	}

	if (channel.has_an_operator() == 0)
		channel.set_random_operator(*this);
}

void Server::quit_all_serv_channels(Client & client, const std::string & msg)
{
	for(t_channels::iterator it = _channels.begin();
		it != _channels.end(); ++it)
	{
		if (it->second.is_join(client))
		{
			it->second.send_quit(client, msg);
			remove_client_from_channel(client, it->second);
		}
	}
}
