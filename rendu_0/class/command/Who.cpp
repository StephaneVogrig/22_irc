/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:02:11 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 14:24:05 by gcannaud         ###   ########.fr       */
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
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		exec_on_user(client, params, server);
	RPL_315_ENDOFWHO(client, server);
}

void Who::exec_on_channel(Client & client, const Params & params, Server & server)
{
	Channel * channel = server.get_channel(params.get_first());
	if (channel != NULL)
		channel->send_who(client, server);
}

void Who::exec_on_user(Client & client, const Params & params, Server & server)
{
	Client * target = server.get_client_by_name(params.get_first());
	if (target != NULL)
	{
		Channel * channel = target->get_last_channel_subscripted();
		RPL_352_WHOREPLY(client, *target, server, channel);
	}
}
