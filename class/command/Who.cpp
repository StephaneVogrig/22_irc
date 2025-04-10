/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:02:11 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 13:13:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"
#include "Server.hpp"

Who::Who() : Command("WHO")
{}

Who::~Who()
{}

void Who::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() < 1)
		ERR_461_NEEDMOREPARAMS(client, "WHO");

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		exec_on_user(client, params, server);
	RPL_315_ENDOFWHO(client);
}

void Who::exec_on_channel(Client & client, const Params & params, Server & server)
{
	const std::string & channel_name = params.get_first();
	Channel * channel = server.get_channel(params.get_first());
	if (channel != NULL)
		channel->send_who(client, server);
}

void Who::exec_on_user(Client & client, const Params & params, Server & server)
{
	Client * target = server.get_client_by_name(params.get_first());
	if (target != NULL)
	{
		std::string flags("H");
		std::string channel_name;
		Channel *channel = target->get_last_channel_subscripted();
		if (!channel)
			channel_name = "*";
		else
		{
			channel_name = channel->get_name();
			if (channel->is_operator(client))
				flags += "*";
		}
		RPL_352_WHOREPLY(client, *target, server, channel_name, flags);
	}
}
