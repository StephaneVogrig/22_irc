/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:03 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/07 19:49:08 by svogrig          ###   ########.fr       */
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
		ERR_NEEDMOREPARAMS(client, "JOIN");

	if (params.get_first() == "0")
	{
		client.quit_all_channels(server);
		return ;
	}

	// convertir params en lsite de channel et liste de key

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
	char prefix = channel_name[0];
	Channel * channel;

	if ( (prefix != '#' && prefix != '&' && prefix != '!' && prefix != '+') || channel_name.size() == 1)
		ERR_NOSUCHCHANNEL(client, channel_name);

	if (client.nbr_channels_subscripted() == MAX_CHANNEL_PER_CLIENT)
		ERR_TOOMANYCHANNELS(client, channel_name);

	std::string status("");
	if (!server.channel_exist(channel_name))
	{
		server.create_channel(channel_name);
		channel = server.get_channel(channel_name);
		status = "Oo";
	}
	else
	{
		channel = server.get_channel(channel_name);
		if (channel == NULL)
			ERR_NOSUCHCHANNEL(client, channel_name);

		// ERR_BADCHANMASK(client, params.get_first()); 476

		if (channel->get_key() != key)
			ERR_BADCHANNELKEY(client, channel_name);

		if (channel->is_banned(client))
			ERR_BANNEDFROMCHAN(client, channel_name);

		if (channel->is_mode_limit_clients() && channel->get_nbr_client() == channel->get_limit_clients())
			ERR_CHANNELISFULL(client, *channel);

		if (channel->is_mode_invite_only() && !channel->is_invited(client))
			ERR_INVITEONLYCHAN(client, channel_name);
	}

	channel->add_client(client, status);

	client.send_msg(":" + client.get_nickname() + " JOIN " + channel->get_name());
	if (channel->get_topic() == "")
	{
		RPL_NOTOPIC(client, *channel);
		return ;
	}
	channel->send_topic();
	// RPL_TOPIC(client, channel);
	RPL_TOPICWHOTIME(client, *channel);
	RPL_NAMREPLY(client, *channel);
	RPL_ENDOFNAMES(client, *channel);
}
