/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:40:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/07 03:38:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

Mode::Mode(void) : Command("MODE")
{}

Mode::~Mode(void)
{}

void Mode::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() == 0)
		ERR_NEEDMOREPARAMS(client, "MODE");

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		exec_on_user(client, params, server);
}

void Mode::exec_on_channel(Client & client, const Params & params, Server & server)
{
	const std::string & channel_name = params.get_first();
	Channel * channel = server.get_channel(channel_name);
	if (channel == NULL)
		ERR_NOSUCHCHANNEL(client, channel_name);

	if (params.get_nbr() == 1)
	{
		RPL_CHANNELMODEIS(client, *channel, server);
		RPL_CREATIONTIME(client, *channel, server);
		return ;
	}

	if (!channel->is_operator(client))
		ERR_CHANOPRIVSNEEDED(client, *channel);

	std::queue<std::string> queue_params;
	for (int i = 1; i < params.get_nbr(); ++i)
		queue_params.push(params.get_param(i));
}

void Mode::exec_on_user(Client & client, const Params & params, Server & server)
{
	(void)client;
	(void)params;
	(void)server;
	// log("exec Mode on user");
	try
	{
		Client & target = server.get_client_by_name(params.get_first());
		(void)target;
	}
	catch(const Server::Client_not_found & e)
	{
        ERR_NOSUCHNICK(client, server, params.get_first());
	}
}
