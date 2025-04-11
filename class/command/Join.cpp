/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:03 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/11 15:21:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join(void) : Command("JOIN")
{}

Join::~Join(void)
{}

void Join::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() < 1)
		ERR_461_NEEDMOREPARAMS(client, "JOIN", server);

	if (params.get_first() == "0")
	{
		client.quit_all_channels(server);
		return ;
	}

	Elements channels(params.get_first());
	std::string  channel_keys;
	if (params.get_nbr() > 1)
		channel_keys = params.get_param(1);
	else
		channel_keys = "";
	Elements keys(channel_keys);

	for (int i = 0; i < channels.get_nbr(); ++i)
	{
		if (i < keys.get_nbr())
			exec_solo(client, channels.get_element(i), keys.get_element(i), server);
		else
			exec_solo(client, channels.get_element(i), "", server);
	}
}

void Join::exec_solo(Client & client, const std::string & channel_name, const std::string & key, Server & server)
{
	try
	{
		if (!Channel::is_a_valid_name(channel_name))
			ERR_476_BADCHANMASK(client, channel_name, server);

		Channel * channel = server.get_channel(channel_name);

		if (channel != NULL && channel->is_join(client))
				return ;

		if (client.nbr_channels_subscripted() == MAX_CHANNEL_PER_CLIENT)
			ERR_405_TOOMANYCHANNELS(client, channel_name, server);

		std::string status;
		if (channel == NULL)
		{
			server.create_channel(channel_name, key);
			channel = server.get_channel(channel_name);
			status = "qo";
		}
		else
		{
			if (channel->is_mode_key_needed() && channel->get_key() != key)
				ERR_475_BADCHANNELKEY(client, channel_name, server);

			if (channel->is_mode_limit_nbr_client() && channel->get_nbr_client() == channel->get_limit_nbr_client())
				ERR_471_CHANNELISFULL(client, *channel, server);

			if (channel->is_mode_invite_only() && !channel->is_invited(client))
				ERR_473_INVITEONLYCHAN(client, channel_name, server);
		}

		channel->add_client(client, status);

		channel->send_msg(client.get_nickname(), "JOIN " + channel->get_name());

		if (channel->get_topic() != "")
		{
			RPL_332_TOPIC(client, *channel);
			RPL_333_TOPICWHOTIME(client, *channel);
		}

		RPL_353_NAMREPLY(client, *channel, server);
		RPL_366_ENDOFNAMES(client, *channel, server);
	}
	catch (const Protocole_error& e)
	{}
}
