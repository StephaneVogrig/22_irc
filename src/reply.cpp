/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/22 01:50:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"

/*
RPL_TOPIC (332)
  "<client> <channel> :<topic>"
Sent to a client when joining the <channel> to inform them of the current topic of the channel.
*/
void rpl_topic(Client & client, Channel & channel)
{
	client.send_msg(":server 332 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic() + "\r\n");
}

/*
RPL_TOPICWHOTIME (333)
  "<client> <channel> <nick> <setat>"
Sent to a client to let them know who set the topic (<nick>) and when they set it (<setat> is a unix timestamp). Sent after RPL_TOPIC (332).
*/
void rpl_topicwhotime(Client & client, Channel & channel)
{
	client.send_msg(":server 333 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic_who() + "\r\n");
}

/*
RPL_NAMREPLY (353)
  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
Sent as a reply to the NAMES command, this numeric lists the clients that are joined to <channel> and their status in that channel.
<symbol> notes the status of the channel. It can be one of the following:
("=", 0x3D) - Public channel.
("@", 0x40) - Secret channel (secret channel mode "+s").
("*", 0x2A) - Private channel (was "+p", no longer widely used today).
<nick> is the nickname of a client joined to that channel, and <prefix> is the highest channel membership prefix that client has in the channel, if they have one. The last parameter of this numeric is a list of [prefix]<nick> pairs, delimited by a SPACE character (' ', 0x20).
*/
void rpl_namereply(Client & client, Channel & channel)
{
	client.send_msg(":server 353 " + client.get_nickname() + " <symbol> " + channel.get_name() + " :" + channel.get_topic_who() + "\r\n");
}

/*
RPL_ENDOFNAMES (366)
  "<client> <channel> :End of /NAMES list"
Sent as a reply to the NAMES command, this numeric specifies the end of a list of channel member names.
*/
void rpl_endofnames(Client & client, Channel & channel)
{
	client.send_msg(":server 366 " + client.get_nickname() + " " + channel.get_name() + " :End of /NAMES list\r\n");
}
