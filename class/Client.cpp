/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:12 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 20:22:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "utils.hpp"

Client::Client(int fd) : _fd(fd), _msg_buffer(""), _nickName("*"), _userName("*"), _hasPass(false), _kicked(false)
{
}

Client::~Client()
{
}

const std::string & Client::get_msg_buffer(void) const
{
	return (_msg_buffer);
}

int Client::get_fd(void)
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

bool Client::is_kicked() const
{
	return _kicked;
}

void Client::set_kicked(bool kick)
{
	_kicked = kick;
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
	std::cout << _fd << " send: " << msg <<std::endl;
	if(send(_fd, msg.c_str(), msg.length(), 0) == -1)
		throw(std::runtime_error("send failed"));
}

std::ostream & operator << (std::ostream & os, const Client & client)
{
	os << "client buffer: " << client.get_msg_buffer();
	return (os);
}
