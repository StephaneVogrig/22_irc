/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:50:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/22 01:17:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string & name)
	:	_name(name), _topic(""), _modes(""), _key("")
{
	std::cout << "created channel " << _name << std::endl;
}

Channel::Channel(const Channel & to_copy) : _name(to_copy._name)
{
	*this = to_copy;
}

Channel::~Channel(void)
{}

Channel & Channel::operator = (const Channel & to_assign)
{
	if (this == &to_assign)
		return *this;
	_topic = to_assign._topic;
	_clients = to_assign._clients;
	_modes = to_assign._modes;
	_invit_list = to_assign._invit_list;
	_key = to_assign._key;
	_limit_clients = to_assign._limit_clients;
	return *this;
}

const std::string & Channel::get_name(void)
{
	return _name;
}

const std::string & Channel::get_topic(void)
{
	return _topic;
}

const std::string & Channel::get_topic_who(void)
{
	return _topic_who;
}

const std::time_t & Channel::get_topic_setat(void)
{
	return _topic_setat;
}

bool Channel::is_mode_invite_only(void)
{
	return _modes.find("i") != std::string::npos;
}

bool Channel::is_invited(const Client & client)
{
	return _invit_list.find(client.get_nickname()) != _invit_list.end();
}

void Channel::add_client(const Client & client, const std::string & status)
{
	if (_clients.find(client.get_nickname()) != _clients.end())
		return ;
	_clients[client.get_nickname()] = status;
	std::cout << client.get_nickname() << " join channel " << get_name() << std::endl;
}

void Channel::remove_client(const Client & client)
{
	_clients.erase(client.get_nickname());
}
