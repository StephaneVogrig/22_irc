/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:54:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/11 16:34:23 by gcannaud         ###   ########.fr       */
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
		ERR_461_NEEDMOREPARAMS(client, "KICK", server);

	Channel * channel = server.get_channel(params.get_first());
	if (channel == NULL)
		ERR_403_NOSUCHCHANNEL(client, params.get_first(), server);

	if (!channel->is_join(client))
		ERR_442_NOTONCHANNEL(client, *channel, server);

	if (!channel->is_operator(client))
		ERR_482_CHANOPRIVSNEEDED(client, *channel, server);

	Elements users(params.get_param(1));
	std::string arg;
	if (params.get_nbr() >= 3)
		arg = params.get_param(2);

	for(int i = users.get_nbr() - 1; i >= 0; --i)
	{
		try
		{
			Client * target = server.get_client_by_name(users.get_element(i));
			if (target == NULL)
				ERR_401_NOSUCHNICK(client, server, users.get_element(i));
			if (channel->is_join(*target))
			{
				channel->send_to_all(client.get_nickname(), "KICK " + channel->get_name() + " " + target->get_nickname() + " " + arg);
				server.remove_client_from_channel(*target, *channel);
			}
			else
				ERR_441_USERNOTINCHANNEL(client, users.get_element(i), *channel, server);
		}
		catch(const Protocole_error& e)
		{}
	}
}
