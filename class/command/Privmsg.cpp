/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/03 17:26:57 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"
#include "Server.hpp"

Privmsg::Privmsg() : Command("Privmsg")
{
}

Privmsg::~Privmsg()
{
}

void Privmsg::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() != 2)
		ERR_NEEDMOREPARAMS(client, "PRIVMSG");

	const std::string & target = params.get_first();
	const std::string & message = params.get_param(1);

	if (message.empty())
		ERR_NOTEXTTOSEND(client);

	if (Channel::is_a_valid_name(target))
	{
		if (!server.channel_exist(target))
			ERR_NOSUCHCHANNEL(client, target);
		Channel * channel = server.get_channel(target);
		if (channel == NULL)
			ERR_NOSUCHCHANNEL(client, target);
		if (!channel->is_join(client))
			ERR_NOTONCHANNEL(client, *channel);
		channel->send_msg(client, message);
	}
	else
	{
		int i;
		for (i = server.get_nbr_connected(); i > 0; --i)
		{
			if (server.get_client_by_idx(i)->get_nickname() == target)
				break;
		}
		if (i == 0)
			ERR_NOSUCHNICK(client, server, target);
		server.get_client_by_idx(i)->send_msg(":" + client.get_nickname() + " PRIVMSG " + target + " :" + message);
	}
}
