/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:54:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/03 17:25:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"
#include "Server.hpp"

Kick::Kick() : Command("KICK")
{}

Kick::~Kick()
{}

void Kick::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() != 2)
		ERR_NEEDMOREPARAMS(client, "KICK");

	Channel * channel = server.get_channel(params.get_first());
	if (channel == NULL)
		ERR_NOSUCHCHANNEL(client, params.get_first());

	if (!channel->is_join(client))
		ERR_NOTONCHANNEL(client, *channel);

	if (!channel->is_operator(client))
		ERR_CHANOPRIVSNEEDED(client, *channel);

	Elements users(params.get_param(1));
	std::string arg;
	if (params.get_nbr() >= 3)
		arg = params.get_param(2);

	for(int i = users.get_nbr() - 1; i >= 0; --i)
	{
		try
		{
			Client & target = server.get_client_by_name(users.get_element(i));
			if (channel->is_join(target))
			{
				server.remove_client_from_channel(target, *channel);
				if (client.get_nickname() != target.get_nickname())
					client.send_msg(":" + client.get_nickname() + " KICK " + channel->get_name() + " " + target.get_nickname() + " " + arg);
				target.send_msg(":" + client.get_nickname() + " KICK " + channel->get_name() + " " + target.get_nickname() + " " + arg);
			}
			else
				ERR_USERNOTINCHANNEL(client, users.get_element(i), *channel);
		}
		catch(const Server::Client_not_found & e)
		{
			try
			{
				ERR_NOSUCHNICK(client, server, users.get_element(i));
			}
			catch(const Protocole_error& e)
			{
			}
		}
	}
}
