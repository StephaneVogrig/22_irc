/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:50:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/19 02:30:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string & name)
	:	_name(name)
{}

Channel::Channel(const Channel & to_copy)
{
	*this = to_copy;
}

Channel::~Channel(void)
{}

Channel & Channel::operator = (const Channel & to_assign)
{
	if (this == &to_assign)
		return (*this);
	_topic = to_assign._topic;
	_clients = to_assign._clients;
	_modes = to_assign._modes;
	_invit_list = to_assign._invit_list;
	_key = to_assign._key;
	_limit_clients = to_assign._limit_clients;
	return (*this);
}

const std::string & Channel::get_name(void)
{
	return (_name);
}

void Channel::add_client(const Client & client)
{
	_clients[client.get_nickname()] = "";
}

void Channel::remove_client(const Client & client)
{
	_clients.erase(client.get_nickname());
}
