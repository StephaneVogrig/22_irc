/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:50:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/09 20:21:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "reply.hpp"
#include "settings.hpp"
#include "Server.hpp"

/* constructor ---------------------------------------------------------------*/

Channel::Channel(const std::string & name, const std::string & key)
	:	_channel_name(name),
		_creation_time(current_time_t()),
		_topic(""),
		_modes(""),
		_key(key),
		_limit_clients(MAX_CLIENT_PER_CHANNEL)
{
	if (!key.empty())
	{
		_modes = "k";
	}
	log("created");
}

Channel::Channel(const Channel & to_copy)
	:	_channel_name(to_copy._channel_name),
		_creation_time(current_time_t())
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

const std::time_t & Channel::get_creation_time() const
{
	return _creation_time;
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

std::string Channel::get_clients()
{
	std::string str;
	for (t_chan_clients::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it != _clients.begin())
			str += " ";
		if (is_founder(*it->second.first))
			str += "~";
		else if (is_operator(*it->second.first))
			str += "@";
		else if (is_halfop(*it->second.first))
			str += "%";
		str += it->first;
	}
	return str;
}

bool Channel::is_mode_invite_only(void)
{
	return _modes.find("i") != std::string::npos;
}

bool Channel::is_mode_protected_topic(void)
{
	return _modes.find("t") != std::string::npos;
}

bool Channel::is_mode_key_needed()
{
	return _modes.find("k") != std::string::npos;
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

bool Channel::is_founder(const Client & client)
{
	return get_client_status(client).find('q') != std::string::npos;
}

bool Channel::is_operator(const Client & client)
{
	return get_client_status(client).find('o') != std::string::npos;
}

bool Channel::is_halfop(const Client & client)
{
	return get_client_status(client).find('h') != std::string::npos;
}

bool Channel::has_an_operator()
{
	for (t_chan_clients::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (is_operator(*it->second.first))
			return true;
	}
	return false;
}

void Channel::set_topic(Client & client, const std::string & topic)
{
	 if (is_mode_protected_topic() && !(is_operator(client) || is_halfop(client)))
		ERR_482_CHANOPRIVSNEEDED(client, *this);
	 _topic = topic;
	 _topic_who = client.get_nickname();
	 time(&_topic_setat);
	 log("set topic to ", _topic);
}

void Channel::set_mode(char c)
{
	_modes += c;
}

void Channel::unset_mode(char c)
{
	std::size_t pos = _modes.find(c);
	if (pos == std::string::npos)
		throw Protocole_error();
	_modes.erase(pos, 1);
}

void Channel::set_key(const std::string & keystring)
{
	_key = keystring;
}

void Channel::set_client_status(const Client & client, char status)
{
	std::string & status_string = _clients.find(client.get_nickname())->second.second;
	if (status_string.find(status) != std::string::npos)
		throw Protocole_error();
	status_string += status;
}

void Channel::unset_client_status(const Client & client, char status)
{
	std::string & status_string = _clients.find(client.get_nickname())->second.second;
	if (status_string.find(status) == std::string::npos)
		return ;
	status_string.erase(status_string.find(status), 1);
}

void Channel::set_limit(int nbr)
{
	_limit_clients = nbr;
}

void Channel::set_random_operator(Server & server)
{
	Client * client = _clients.begin()->second.first;
	std::string & status = _clients.begin()->second.second;
	status += 'o';
	send_msg(server.get_name(), "MODE " + _channel_name + " +o " + client->get_nickname());
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
	log("add", client.get_nickname());
}

void Channel::remove_client(Client & client)
{
	_clients.erase(client.get_nickname());
	client.remove_channel_subscripted(*this);
	log("remove", client.get_nickname());
}

void Channel::send_msg(const std::string & sender, const std::string & msg)
{
	std::string irc_msg = ":" + sender + " " + msg;

	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		it->second.first->send_msg(irc_msg);
	}
}

void Channel::send_priv_msg(const Client & sender, const std::string & msg)
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
		it->second.first->send_msg(RPL_332_TOPIC_(it->second.first->get_nickname(), _channel_name, _topic));
	}
}

void Channel::send_who(Client & sender, Server & server)
{
	for (std::map<std::string, std::pair<Client *, std::string> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		std::string flags("H");
		if (get_client_status(*it->second.first).find("o") != std::string::npos)
			flags += "*";
		RPL_352_WHOREPLY(sender, *it->second.first, server, _channel_name, flags);
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

void Channel::log(const std::string & action)
{
	log_(FG_YELLOW "channel " RESET + _channel_name + FG_YELLOW " : " + action + RESET);
}


void Channel::log(const std::string & action, const std::string & who)
{
	log_(FG_YELLOW "channel " RESET + _channel_name + FG_YELLOW " : " + action + " " RESET + who);
}
