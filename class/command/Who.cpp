/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:02:11 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/08 13:38:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"
#include "Server.hpp"

Who::Who() : Command("WHO")
{
}

Who::~Who()
{
}

void Who::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() < 1)
		ERR_461_NEEDMOREPARAMS(client, "WHO");

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		exec_on_user(client, params, server);
}

void Who::exec_on_channel(Client & client, const Params & params, Server & server)
{
	const std::string & channel_name = params.get_first();
	if (!server.channel_exist(channel_name))
		RPL_318_ENDOFWHOIS(client, params.get_first());
	Channel * channel = server.get_channel(params.get_first());
	if (channel == NULL)
		ERR_403_NOSUCHCHANNEL(client, params.get_first());
	channel->send_who(client, server);
	RPL_315_ENDOFWHO(client);
}

void Who::exec_on_user(Client & client, const Params & params, Server & server)
{
	Client * target = server.get_client_by_name(params.get_first());
	if (target != NULL)
	{
		Channel *channel = target->get_last_channel_subscripted();
		if (!channel)
		{
			RPL_352_WHOREPLY(client, *target, server, "*", "H");
			return ;
		}
		if (channel->is_join(*target))
		{
			std::string flags("H");
			if (channel->get_client_status(*target).find("o") != std::string::npos)
				flags += "*";
			RPL_352_WHOREPLY(client, *target, server, channel->get_name(), flags);
		}
	}
	RPL_315_ENDOFWHO(client);
}
