/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:36:45 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 17:43:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

/* constructor ---------------------------------------------------------------*/

Topic::Topic(void) : Command("TOPIC")
{}

/* destructor ----------------------------------------------------------------*/

Topic::~Topic(void)
{}

/* utilities -----------------------------------------------------------------*/

void Topic::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() < 1)
		ERR_NEEDMOREPARAMS(client, _name);

	Channel * channel = server.get_channel(params.get_first());
	if (!channel->is_join(client))
		ERR_NOTONCHANNEL(client, *channel);

	if (params.get_nbr() == 1)
	{
		if (channel->get_topic().empty())
			RPL_NOTOPIC(client, *channel);
		else
		{
			client.send_msg(RPL_TOPIC_(client.get_nickname(), channel->get_name(), channel->get_topic()));
			RPL_TOPICWHOTIME(client, *channel);
		}
		return ;
	}
	const std::string & topic = params.get_param(1);
	channel->set_topic(client, topic);
	channel->send_topic();
}
