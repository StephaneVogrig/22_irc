/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:36:45 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/11 16:34:39 by gcannaud         ###   ########.fr       */
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
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	const std::string & channel_name = params.get_first();
	Channel * channel = server.get_channel(channel_name);
	if (channel == NULL)
		ERR_403_NOSUCHCHANNEL(client, channel_name, server);

	if (!channel->is_join(client))
		ERR_442_NOTONCHANNEL(client, *channel, server);

	if (channel->is_mode_protected_topic()
	&& !channel->is_operator(client)
	&& channel->is_halfop(client))
		ERR_482_CHANOPRIVSNEEDED(client, *channel, server);

	if (params.get_nbr() == 1)
	{
		if (channel->get_topic().empty())
			RPL_331_NOTOPIC(client, *channel, server);
		else
		{
			client.send_msg(RPL_332_TOPIC_(client.get_nickname(), channel->get_name(), channel->get_topic()));
			RPL_333_TOPICWHOTIME(client, *channel);
		}
		return ;
	}
	const std::string & topic = params.get_param(1);
	channel->set_topic(client, topic, server);
	channel->send_to_all(client.get_nickname(), "TOPIC " + channel->get_name() + " :" + channel->get_topic());
}
