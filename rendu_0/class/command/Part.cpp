/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:47:39 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:18:01 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

Part::Part() : Command("PART")
{}

Part::~Part()
{}

void Part::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() < 1)
		ERR_461_NEEDMOREPARAMS(client, _name, server);

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
				ERR_403_NOSUCHCHANNEL(client, channel_name, server);

			if (!channel->is_join(client))
				ERR_442_NOTONCHANNEL(client, *channel, server);

			channel->send_to_all(client.get_nickname(), _name + " " + channel->get_name() + " :" + arg);
			server.remove_client_from_channel(client, *channel);
		}
		catch (const Protocole_error &e)
		{}
	}
}
