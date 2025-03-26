/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:03 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 12:59:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join(void) : Command("JOIN")
{}

Join::~Join(void)
{}

void Join::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_first() == "0")
	{
		// quitter tous les channels auxquels le client est inscrit
		return ;
	}

	std::string status("");
	if (!server.channel_exist(params.get_first()))
	{
		server.create_channel(params.get_first());
		status = "O";
	}
	Channel & channel = server.get_channel(params.get_param(0));

/*
ERR_NEEDMOREPARAMS (461)
  "<client> <command> :Not enough parameters"
Returned when a client command cannot be parsed because not enough parameters were supplied. The text used in the last param of this message may vary.
*/

/*
ERR_NOSUCHCHANNEL (403)
  "<client> <channel> :No such channel"
Indicates that no channel can be found for the supplied channel name. The text used in the last param of this message may vary.
*/

/*
ERR_TOOMANYCHANNELS (405)
  "<client> <channel> :You have joined too many channels"
Indicates that the JOIN command failed because the client has joined their maximum number of channels. The text used in the last param of this message may vary.
*/

/*
ERR_BADCHANNELKEY (475)
  "<client> <channel> :Cannot join channel (+k)"
Returned to indicate that a JOIN command failed because the channel requires a key and the key was either incorrect or not supplied. The text used in the last param of this message may vary.

Not to be confused with ERR_INVALIDKEY, which may be returned when setting a key.
*/

/*
ERR_BANNEDFROMCHAN (474)
  "<client> <channel> :Cannot join channel (+b)"
Returned to indicate that a JOIN command failed because the client has been banned from the channel and has not had a ban exception set for them. The text used in the last param of this message may vary.
*/

/*
ERR_CHANNELISFULL (471)
  "<client> <channel> :Cannot join channel (+l)"
Returned to indicate that a JOIN command failed because the client limit mode has been set and the maximum number of users are already joined to the channel. The text used in the last param of this message may vary.
*/
/*
ERR_INVITEONLYCHAN (473)
  "<client> <channel> :Cannot join channel (+i)"
Returned to indicate that a JOIN command failed because the channel is set to [invite-only] mode and the client has not been invited to the channel or had an invite exception set for them. The text used in the last param of this message may vary.
*/
	if (channel.is_mode_invite_only() && !channel.is_invited(client))
	{
		//ERR_INVITEONLYCHAN
		return ;
	}

/*
ERR_BADCHANMASK (476)
  "<channel> :Bad Channel Mask"
Indicates the supplied channel name is not a valid.

This is similar to, but stronger than, ERR_NOSUCHCHANNEL (403), which indicates that the channel does not exist, but that it may be a valid name.

The text used in the last param of this message may vary.
*/

	channel.add_client(client, status);


	client.send_msg(":" + client.get_nickname() + " JOIN " + channel.get_name() + "\r\n");
	if (channel.get_topic() == "")
	{
		rpl_topic(client, channel);
		rpl_topicwhotime(client, channel);
	}
	rpl_namereply(client, channel);
	rpl_endofnames(client, channel);
}
