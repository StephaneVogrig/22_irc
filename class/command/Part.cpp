/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:47:39 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/03 13:07:41 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"
#include "Server.hpp"

Part::Part() : Command("PART")
{}

Part::~Part()
{}

void Part::exec(Client & client, const Params & params, Server & server)
{
	if (!client.is_registed())
		ERR_NOTREGISTERED(client, server);

	if (params.get_nbr() < 2)
		ERR_NEEDMOREPARAMS(client, "PART");

	Elements channels(params.get_first());
	std::string arg;
	if (params.get_nbr() >= 2)
		arg = params.get_param(1);

	for(int i = 0; i < channels.get_nbr(); ++i)
	{
		try
		{
			const std::string & channel_name = channels.get_element(i);
			Channel * channel = server.get_channel(channel_name);
			if (channel == NULL)
				ERR_NOSUCHCHANNEL(client, channel_name);

			if (!channel->is_join(client))
				ERR_NOTONCHANNEL(client, *channel);

			//channel->remove_client(client);
			server.remove_client_from_channel(client, *channel);
			client.send_msg(":" + client.get_nickname() + " PART " + channel->get_name() + " " + arg);
		}
		catch (const Protocole_error &e)
		{}
	}
}
