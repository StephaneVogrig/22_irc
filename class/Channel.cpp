/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:50:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 14:01:13 by gcannaud         ###   ########.fr       */
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
		_limit_nbr_client(MAX_CLIENT_PER_CHANNEL)
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
	_topic				= to_assign._topic;
	_chan_clients		= to_assign._chan_clients;
	_modes				= to_assign._modes;
	_invited 		= to_assign._invited;
	_key				= to_assign._key;
	_limit_nbr_client	= to_assign._limit_nbr_client;
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

const std::string & Channel::get_client_status(const Client & client) const
{
	return _chan_clients.find(client.get_fd())->second.second;
}

int  Channel::get_limit_nbr_client() const
{
	return _limit_nbr_client;
}

int  Channel::get_nbr_client() const
{
	return _chan_clients.size();
}

std::string Channel::get_clients() const
{
	std::string str;
	for (t_chan_clients::const_iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
	{
		if (it != _chan_clients.begin())
			str += " ";

		if (is_operator(*it->second.first))
			str += "@";
		else if (is_halfop(*it->second.first))
			str += "%";
		str += it->second.first->get_nickname();
	}
	return str;
}

bool Channel::is_mode_invite_only(void) const
{
	return _modes.find("i") != std::string::npos;
}

bool Channel::is_mode_protected_topic(void) const
{
	return _modes.find("t") != std::string::npos;
}

bool Channel::is_mode_key_needed() const
{
	return _modes.find("k") != std::string::npos;
}

bool Channel::is_mode_limit_nbr_client(void) const
{
	return _modes.find("l") != std::string::npos;
}

bool Channel::is_join(const Client & client) const
{
	return _chan_clients.find(client.get_fd()) != _chan_clients.end();
}

bool Channel::is_invited(const Client & client) const
{
	return _invited.find(client.get_fd()) != _invited.end();
}

bool Channel::is_founder(const Client & client) const
{
	return get_client_status(client).find('q') != std::string::npos;
}

bool Channel::is_operator(const Client & client) const
{
	return get_client_status(client).find('o') != std::string::npos;
}

bool Channel::is_halfop(const Client & client) const
{
	return get_client_status(client).find('h') != std::string::npos;
}

bool Channel::has_an_operator() const
{
	for (t_chan_clients::const_iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
	{
		if (is_operator(*it->second.first))
			return true;
	}
	return false;
}

void Channel::set_topic(Client & client, const std::string & topic, Server & server)
{
	 if (is_mode_protected_topic() && !(is_operator(client) || is_halfop(client)))
		ERR_482_CHANOPRIVSNEEDED(client, *this, server);
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
	std::string & status_string = _chan_clients.find(client.get_fd())->second.second;
	if (status_string.find(status) != std::string::npos)
		throw Protocole_error();
	status_string += status;
}

void Channel::unset_client_status(const Client & client, char status)
{
	std::string & status_string = _chan_clients.find(client.get_fd())->second.second;
	if (status_string.find(status) == std::string::npos)
		throw Protocole_error();
	status_string.erase(status_string.find(status), 1);
}

void Channel::set_limit(int nbr)
{
	_limit_nbr_client = nbr;
}

void Channel::set_random_operator(Server & server)
{
	Client * client = _chan_clients.begin()->second.first;
	std::string & status = _chan_clients.begin()->second.second;
	status += 'o';
	send_to_all(server.get_name(), "MODE " + _channel_name + " +o " + client->get_nickname());
}

bool Channel::is_a_valid_name(const std::string & str)
{
	char prefix = str[0];

	if (prefix != '#' && prefix != '&' && prefix != '!' && prefix != '+')
		return (false);
	if (str.size() == 1 )
		return (false);
	if (str.find(' ') != std::string::npos)
		return (false);
	if (str.find('\a') != std::string::npos)
		return (false);
	return (true);
}

void Channel::invite_client(const Client & client)
{
	_invited.insert(client.get_fd());
}

void Channel::remove_from_invited(const Client & client)
{
	t_invited::iterator it = _invited.find(client.get_fd());
	if (it != _invited.end())
		_invited.erase(it);
}

/* utilities -----------------------------------------------------------------*/

void Channel::add_client(Client & client, const std::string & status)
{
	if (_chan_clients.find(client.get_fd()) != _chan_clients.end())
		return ;

	t_invited::iterator it = _invited.find(client.get_fd());
	if (it != _invited.end())
		_invited.erase(it);

	_chan_clients[client.get_fd()].first = &client;
	_chan_clients[client.get_fd()].second = status;
	client.add_channel_subscripted(*this);
	log("add", client.get_nickname());
}

void Channel::remove_client(Client & client)
{
	_chan_clients.erase(client.get_fd());
	client.remove_channel_subscripted(*this);
	log("remove", client.get_nickname());
}

void Channel::send_to_all(const std::string & sender, const std::string & msg)
{
	std::string irc_msg = ":" + sender + " " + msg;
	for (t_chan_clients::iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
	{
		it->second.first->send_msg(irc_msg);
	}
}

void Channel::send_to_others(const Client & sender, const std::string & cmd, const std::string & msg)
{
	std::string irc_msg = ":" + sender.get_nickname() + " " + cmd + " " + _channel_name;

	for (t_chan_clients::iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
	{
		if (it->first != sender.get_fd())
			it->second.first->send_msg(irc_msg + " :" + msg);
	}
}

void Channel::send_who(Client & sender, Server & server)
{
	for (t_chan_clients::iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
	{
		RPL_352_WHOREPLY(sender, *it->second.first, server, this);
	}
}

void Channel::send_quit(Client & sender, const std::string & msg)
{
	for (t_chan_clients::iterator it = _chan_clients.begin(); it != _chan_clients.end(); ++it)
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
