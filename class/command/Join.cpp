/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:03 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 18:38:06 by svogrig          ###   ########.fr       */
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
		client.quit_all_channels();
		return ;
	}

	// convertir params en lsite de channel et liste de key

	Elements channels(params.get_first());
	log("channels: " + to_string(channels));
	const std::string & chan_name = params.get_first();
	std::string  channel_key;
	if (params.get_nbr() > 1)
		channel_key = params.get_param(1);
	else
		channel_key = "";

	char prefix = chan_name[0];
	if ( (prefix != '#' && prefix != '&' && prefix != '!' && prefix != '+') || chan_name.size() == 1)
		ERR_NOSUCHCHANNEL(client, params.get_first());

	if (client.nbr_channels_subscripted() == MAX_CHANNEL_PER_CLIENT)
		ERR_TOOMANYCHANNELS(client, params.get_first());

	std::string status("");
	if (!server.channel_exist(chan_name))
	{
		server.create_channel(chan_name);
		status = "Oo";
	}

	Channel * channel = server.get_channel(chan_name);

/*
ERR_NOSUCHCHANNEL (403)
  "<client> <channel> :No such channel"
Indicates that no channel can be found for the supplied channel name. The text used in the last param of this message may vary.
*/

	// ERR_BADCHANMASK(client, params.get_first()); 476

	if (channel->get_key() != channel_key)
		ERR_BADCHANNELKEY(client, chan_name);

	if (channel->is_banned(client))
		ERR_BANNEDFROMCHAN(client, chan_name);

	channel->add_client(client, status);

/*
ERR_CHANNELISFULL (471)
  "<client> <channel> :Cannot join channel (+l)"
Returned to indicate that a JOIN command failed because the client limit mode has been set and the maximum number of users are already joined to the channel. The text used in the last param of this message may vary.
*/

	if (channel->is_mode_invite_only() && !channel->is_invited(client))
		ERR_INVITEONLYCHAN(client, chan_name);
	channel->add_client(client, status);

	client.send_msg(":" + client.get_nickname() + " JOIN " + channel->get_name());
	if (channel->get_topic() == "")
	{
		channel->send_topic();
		// RPL_TOPIC(client, channel);
		RPL_TOPICWHOTIME(client, *channel);
	}
	RPL_NAMREPLY(client, *channel);
	RPL_ENDOFNAMES(client, *channel);
}
