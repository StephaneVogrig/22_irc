/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:17:32 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"

Privmsg::Privmsg() : Command("PRIVMSG")
{}

Privmsg::~Privmsg()
{}

void Privmsg::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() != 2)
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	const std::string & target = params.get_first();
	const std::string & message = params.get_param(1);

	if (message.empty())
		ERR_412_NOTEXTTOSEND(client, server);

	if (Channel::is_a_valid_name(target))
	{
		Channel * channel = server.get_channel(target);
		if (channel == NULL)
			ERR_403_NOSUCHCHANNEL(client, target, server);

		if (!channel->is_join(client))
			ERR_442_NOTONCHANNEL(client, *channel, server);

		channel->send_to_others(client, _name, message);
	}
	else
	{
		Client * c_target = server.get_client_by_name(target);
		if (c_target == NULL)
			ERR_401_NOSUCHNICK(client, server, target);

		c_target->send_msg(":" + client.get_nickname() + " " + _name + " " + target + " :" + message);
	}
}
