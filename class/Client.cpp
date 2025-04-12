/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:12 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/11 16:35:28 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include "log.hpp"
#include "Server.hpp"

/* constructor ---------------------------------------------------------------*/

Client::Client(int fd, struct sockaddr_in addr)
	:	_fd(fd),
		_msg_buffer(""),
		_nickName("*"),
		_userName("*"),
		_hostadress(inet_ntoa(addr.sin_addr)),
		_port(ntohs(addr.sin_port)),
		_connection_ko(false),
		_hasPass(false)
{}

/* destructor ----------------------------------------------------------------*/

Client::~Client()
{}

/* operator ------------------------------------------------------------------*/

std::ostream & operator << (std::ostream & os, const Client & client)
{
	os << "client buffer: " << client.get_msg_buffer();
	return (os);
}

/* accessor ------------------------------------------------------------------*/

const std::string & Client::get_msg_buffer(void) const
{
	return (_msg_buffer);
}

int Client::get_fd(void) const
{
	return _fd;
}

const std::string Client::get_nickname(void) const
{
	return (_nickName);
}

const std::string Client::get_username(void) const
{
	return (_userName);
}

const std::string Client::get_realname(void) const
{
	return (_realName);
}

const std::string Client::get_hostname() const
{
	return (_hostname);
}

const std::string Client::get_hostadress() const
{
	return (_hostadress);
}

bool Client::is_registed() const
{
	if (_nickName != "*" && _userName != "*")
		return 1;
	return 0;
}

bool Client::is_hasPass() const
{
	return _hasPass;
}

void Client::set_hasPass(bool pass)
{
	_hasPass = pass;
}

void Client::set_nickname(std::string name)
{
	_nickName = name;
}

void Client::set_username(std::string name)
{
	_userName = name;
}

void Client::set_realname(std::string name)
{
	_realName = name;
}

/* utilities -----------------------------------------------------------------*/

void Client::append_to_buffer(const std::string & str)
{
	_msg_buffer.append(str);
}

void Client::clear_msg_buffer(void)
{
	_msg_buffer.clear();
}

void Client::send_msg(const std::string & msg)
{
	if (_connection_ko)
		return ;
	if(send(_fd, (msg + "\r\n").c_str(), msg.length() + 2, MSG_NOSIGNAL) == -1)
	{
		log_msg(_fd, FG_RED "xx" FG_PURPLE, msg);
		_connection_ko = true;
		return ;
	}
	log_msg(_fd, FG_GREEN ">>", msg);
}

void Client::add_channel_subscripted(Channel & channel)
{
	_channels_subscripted.push_back(&channel);
}

Channel * Client::get_last_channel_subscripted()
{
	if (_channels_subscripted.size() == 0)
		return (NULL);
	return (_channels_subscripted.back());
}

void Client::remove_channel_subscripted(Channel & channel)
{
	t_channels::iterator it = std::find(_channels_subscripted.begin(), _channels_subscripted.end(), &channel);
	if (it != _channels_subscripted.end())
		_channels_subscripted.erase(it);
}

int  Client::nbr_channels_subscripted()
{
	return _channels_subscripted.size();
}

void Client::quit_all_channels(Server & server)
{
	while (_channels_subscripted.size() > 0)
	{
		server.remove_client_from_channel(*this, *_channels_subscripted.back());
	}
}

void Client::quit_quit_all_channels(Server & server, const std::string & msg)
{
	while (_channels_subscripted.size() > 0)
	{
		std::string channel_name = _channels_subscripted.back()->get_name();
		server.remove_client_from_channel(*this, *_channels_subscripted.back());
		if (server.channel_exist(channel_name))
			server.get_channel(channel_name)->send_to_all(_nickName, msg);
	}
}
