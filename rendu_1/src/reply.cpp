/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 20:44:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"
#include "Server.hpp"

void RPL_001_WELCOME(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 001 " + client.get_nickname() + " :Welcome to the " + server.get_name() + " IRC Network, " + client.get_nickname());
}

void RPL_002_YOURHOST(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 002 " + client.get_nickname() + " :Your host is " + server.get_name() + ", running version "  + server.get_verstion());
}

void RPL_003_CREATED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 003 " + client.get_nickname() + " :This server was created " + server.get_creation_date_time());
}

void RPL_004_MYINFO(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 004 " + client.get_nickname() + " " + server.get_name() + " " + server.get_verstion() + " * ikloqt klo");
}

void RPL_315_ENDOFWHO(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 315 " + client.get_nickname() + " :End of WHO list");
}

void RPL_322_LIST(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 322 " + client.get_nickname() + " " + channel.get_name() + " " + to_string(channel.get_nbr_client()) + " : " + channel.get_topic());
}

void RPL_323_LISTEND(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 323 :End of /LIST");
}

void RPL_324_CHANNELMODEIS(Client & client, Channel & channel, Server & server)
{
	const std::string & modestr = channel.get_modes();
	std::string params;
	for (std::string::const_iterator it = modestr.begin(); it != modestr.end(); ++it)
	{
		if (channel.is_join(client))
		{
			if (*it == 'l')
				params += " " + to_string(channel.get_limit_nbr_client());
			if (*it == 'k')
				params +=  " " + channel.get_key();
		}
		else
		{
			if (*it == 'l')
				params +=  " **";
			if (*it == 'k')
				params +=  " *****";
		}
	}
	client.send_msg(":" + server.get_name() + " 324 " + client.get_nickname() + " " + channel.get_name() + " +" + modestr + params);
}

void RPL_329_CREATIONTIME(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 329 " + client.get_nickname() + " " + channel.get_name() + " " + to_string(channel.get_creation_time()));
}

void RPL_331_NOTOPIC(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 331 " + client.get_nickname() + " " + channel.get_name() + " :No topic is set");
}

void RPL_332_TOPIC(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 332 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic());
}

void RPL_333_TOPICWHOTIME(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 333 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic_who() + " " + to_string(channel.get_topic_setat()));
}

void RPL_341_INVITING(Client & client, const std::string & name, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 341 " + client.get_nickname() + " " + name + " " + channel.get_name());
}

void RPL_352_WHOREPLY(Client & client, Client & target, Server & server, Channel * channel)
{
	std::string flags("H");
	std::string channel_name;
	if (!channel)
			channel_name = "*";
	else
	{
		channel_name = channel->get_name();
		if (channel->is_operator(target))
			flags += "@";
	}
	client.send_msg(":" + server.get_name() + " 352 " + client.get_nickname() + " " + channel_name + " " + target.get_username() + " " + client.get_hostadress() + " " + server.get_name() + " " + target.get_nickname() + " " + flags + " :0 " + target.get_realname());
}

void RPL_353_NAMREPLY(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 353 " + client.get_nickname() + " = " + channel.get_name() + " :" + channel.get_clients());
}

void RPL_366_ENDOFNAMES(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 366 " + client.get_nickname() + " " + channel.get_name() + " :End of /NAMES list");
}
