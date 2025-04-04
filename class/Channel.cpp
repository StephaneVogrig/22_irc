/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:50:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/03 12:55:13 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "reply.hpp"
#include "settings.hpp"
#include "Server.hpp"

/* constructor ---------------------------------------------------------------*/

Channel::Channel(const std::string & name)
	:	_channel_name(name),
		_topic(""),
		_modes(""),
		_key(""),
		_limit_clients(MAX_CLIENT_PER_CHANNEL)
{
	log_channel(_channel_name, "created", "");
}

Channel::Channel(const Channel & to_copy) : _channel_name(to_copy._channel_name)
{
	*this = to_copy;
}

/* destructor ----------------------------------------------------------------*/

Channel::~Channel(void)
{}

/* operator ------------------------------------------------------------------*/

Channel & Channel::operator = (const Channel & to_assign)
{
	if (this == &to_assign)
		return *this;
	_topic			= to_assign._topic;
	_clients		= to_assign._clients;
	_modes			= to_assign._modes;
	_invit_list 	= to_assign._invit_list;
	_key			= to_assign._key;
	_limit_clients	= to_assign._limit_clients;
	return *this;
}

/* accessor ------------------------------------------------------------------*/

const std::string & Channel::get_name(void) const
{
	return _channel_name;
}

const std::string & Channel::get_topic(void) const
{
	return _topic;
}

const std::string & Channel::get_topic_who(void) const
{
	return _topic_who;
}

const std::time_t & Channel::get_topic_setat(void) const
{
	return _topic_setat;
}
const std::string & Channel::get_modes() const
{
	return _modes;
}

const std::string & Channel::get_key(void) const
{
	return _key;
}

const std::string & Channel::get_client_status(const Client & client)
{
	return _clients.find(client.get_nickname())->second.second;
}

int  Channel::get_limit_clients()
{
	return _limit_clients;
}

int  Channel::get_nbr_client() const
{
	return _clients.size();
}

bool Channel::is_mode_invite_only(void)
{
	return _modes.find("i") != std::string::npos;
}

bool Channel::is_mode_protected_topic(void)
{
	return _modes.find("t") != std::string::npos;
}

bool Channel::is_mode_limit_clients(void)
{
	return _modes.find("l") != std::string::npos;
}

bool Channel::is_join(const Client & client)
{
	return _clients.find(client.get_nickname()) != _clients.end();
}

bool Channel::is_invited(const Client & client)
{
	return _invit_list.find(client.get_nickname()) != _invit_list.end();
}

bool Channel::is_banned(const Client & client)
{
	return _banned_list.find(client.get_nickname()) != _banned_list.end();
}

bool Channel::is_operator(const Client & client)
{
	return get_client_status(client).find('o') != std::string::npos;
}

bool Channel::is_halfop(const Client & client)
{
	return get_client_status(client).find('h') != std::string::npos;
}

void Channel::set_topic(const Client & client, const std::string & topic)
{
	 if (is_mode_protected_topic() && !(is_operator(client) || is_halfop(client)))
		ERR_CHANOPRIVSNEEDED(client, *this);
	 _topic = topic;
	 _topic_who = client.get_nickname();
	 time(&_topic_setat);
	 log("set topic to: " + _topic);
}

bool Channel::is_a_valid_name(const std::string & str)
{
	char prefix = str[0];
	if ( (prefix == '#' || prefix == '&' || prefix == '!' || prefix == '+'))
		return (true);
	return (false);
}

void Channel::invite_client(const std::string & name)
{
	_invit_list.insert(name);
}

/* utilities -----------------------------------------------------------------*/

void Channel::add_client(Client & client, const std::string & status)
{
	if (_clients.find(client.get_nickname()) != _clients.end())
		return ;
	_clients[client.get_nickname()].first = &client;
	_clients[client.get_nickname()].second = status;
	client.add_channel_subscripted(*this);

	log_channel(_channel_name, "add", client.get_nickname());
	send_msg(client, client.get_nickname() + " join channel");
}

void Channel::remove_client(Client & client)
{
	_clients.erase(client.get_nickname());
	client.remove_channel_subscripted(*this);
	log_channel(_channel_name, "remove", client.get_nickname());
	send_msg(client, client.get_nickname() + " quit channel");
}

void Channel::send_msg(const Client & sender, const std::string & msg)
{
	std::string irc_msg = ":" + sender.get_nickname() + " PRIVMSG ";

	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first != sender.get_nickname())
			it->second.first->send_msg(irc_msg + _channel_name + " :" + msg);
	}
}

void Channel::send_topic()
{
	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		it->second.first->send_msg(RPL_TOPIC_(it->second.first->get_nickname(), _channel_name, _topic));
	}
}

void Channel::send_who(Client & sender, Server & server)
{
	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		RPL_WHOREPLY(sender, *it->second.first, server, _channel_name);
	}
}

void Channel::send_quit(Client & sender, const std::string & msg)
{
	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (sender.get_nickname() != it->second.first->get_nickname())
			it->second.first->send_msg(":" + sender.get_nickname() + " QUIT :" + msg);
	}
}
