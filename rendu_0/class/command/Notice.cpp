/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:47:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Notice.hpp"

Notice::Notice() : Command("NOTICE")
{}

Notice::~Notice()
{}

void Notice::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() != 2)
		throw Protocole_error();

	const std::string & target = params.get_first();
	const std::string & message = params.get_param(1);

	if (message.empty())
		throw Protocole_error();

	if (Channel::is_a_valid_name(target))
	{
		if (!server.channel_exist(target))
			throw Protocole_error();

		Channel * channel = server.get_channel(target);
		if (channel == NULL)
			throw Protocole_error();
		if (!channel->is_join(client))
			throw Protocole_error();

		channel->send_to_others(client, _name, message);
	}
	else
	{
		Client * c_target = server.get_client_by_name(target);
		if (c_target == NULL)
			throw Protocole_error();

		c_target->send_msg(":" + client.get_nickname() + " " + _name + " " + target + " :" + message);
	}
}
