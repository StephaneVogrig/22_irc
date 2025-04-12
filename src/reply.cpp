/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/12 17:05:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"
#include "Server.hpp"

/*
	Command responses
	https://modern.ircdocs.horse/

	previous: https://www.rfc-editor.org/rfc/rfc2812#section-5.1
*/

/*
RPL_WELCOME (001)
  "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
The first message sent after client registration, this message introduces the client to the network. The text used in the last param of this message varies wildly.

Servers that implement spoofed hostmasks in any capacity SHOULD NOT include the extended (complete) hostmask in the last parameter of this reply, either for all clients or for those whose hostnames have been spoofed. This is because some clients try to extract the hostname from this final parameter of this message and resolve this hostname, in order to discover their ‘local IP address’.

Clients MUST NOT try to extract the hostname from the final parameter of this message and then attempt to resolve this hostname. This method of operation WILL BREAK and will cause issues when the server returns a spoofed hostname.
*/
void RPL_001_WELCOME(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 001 " + client.get_nickname() + " :Welcome to the " + server.get_name() + " IRC Network, " + client.get_nickname());
}

/*
 RPL_ENDOFWHO (315)

  "<client> <mask> :End of WHO list"

Sent as a reply to the WHO command, this numeric indicates the end of a WHO response for the mask <mask>.

<mask> MUST be the same <mask> parameter sent by the client in its WHO message, but MAY be casefolded.

This numeric is sent after all other WHO response numerics have been sent to the client.
*/
void RPL_315_ENDOFWHO(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 315 " + client.get_nickname() + " :End of WHO list");
}

/*
318	RPL_ENDOFWHOIS
		"<nick> :End of WHOIS list"
*/
void RPL_318_ENDOFWHOIS(Client & client, const std::string & name)
{
	client.send_msg(":server 318 " + client.get_nickname() + " " + name + " :End of /WHOIS list");
}

/*
RPL_CHANNELMODEIS (324)
  "<client> <channel> <modestring> <mode arguments>..."
Sent to a client to inform them of the currently-set modes of a channel. <channel> is the name of the channel. <modestring> and <mode arguments> are a mode string and the mode arguments (delimited as separate parameters) as defined in the MODE message description.
*/
void RPL_324_CHANNELMODEIS(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 324 " + client.get_nickname() + " " + channel.get_name() + " " + channel.get_modes());
}

/*
RPL_CREATIONTIME (329)
  "<client> <channel> <creationtime>"
Sent to a client to inform them of the creation time of a channel. <channel> is the name of the channel. <creationtime> is a unix timestamp representing when the channel was created on the network.
*/
void RPL_329_CREATIONTIME(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 329 " + client.get_nickname() + " " + channel.get_name() + " " + to_string(channel.get_creation_time()));
}

/*
RPL_NOTOPIC (331)
  "<client> <channel> :No topic is set"
Sent to a client when joining a channel to inform them that the channel with the name <channel> does not have any topic set.
*/
void RPL_331_NOTOPIC(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 331 " + client.get_nickname() + " " + channel.get_name() + " :No topic is set");
}

/*
RPL_TOPIC (332)
  "<client> <channel> :<topic>"
Sent to a client when joining the <channel> to inform them of the current topic of the channel.
*/
void RPL_332_TOPIC(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 332 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic());
}

/*
RPL_TOPICWHOTIME (333)
  "<client> <channel> <nick> <setat>"
Sent to a client to let them know who set the topic (<nick>) and when they set it (<setat> is a unix timestamp). Sent after RPL_TOPIC (332).
*/
void RPL_333_TOPICWHOTIME(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 333 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic_who() + " " + to_string(channel.get_topic_setat()));
}

/*
341	RPL_INVITING
		"<channel> <nick>"

	- Returned by the server to indicate that the
	attempted INVITE message was successful and is
	being passed onto the end client.
*/
void RPL_341_INVITING(Client & client, const std::string & name, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 341 " + client.get_nickname() + " " + name + " " + channel.get_name());
}

/*
352	RPL_352_WHOREPLY
		"<channel> <user> <host> <server> <nick>
		( "H" / "G" > ["*"] [ ( "@" / "+" ) ]
		:<hopcount> <real name>"
*/
void RPL_352_WHOREPLY(Client & client, Client & target, Server & server, const std::string & channel_name, const std::string & flags)
{
	client.send_msg(":" + server.get_name() + " 352 " + client.get_nickname() + " " + channel_name + " " + target.get_username() + " " + client.get_hostadress() + " " + server.get_name() + " " + target.get_nickname() + " " + flags + " :0 " + target.get_realname());
}

/*
RPL_353_NAMREPLY (353)
  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
Sent as a reply to the NAMES command, this numeric lists the clients that are joined to <channel> and their status in that channel.

<symbol> notes the status of the channel. It can be one of the following:

("=", 0x3D) - Public channel.
("@", 0x40) - Secret channel (secret channel mode "+s").
("*", 0x2A) - Private channel (was "+p", no longer widely used today).
<nick> is the nickname of a client joined to that channel, and <prefix> is the highest channel membership prefix that client has in the channel, if they have one. The last parameter of this numeric is a list of [prefix]<nick> pairs, delimited by a SPACE character (' ', 0x20).
*/
void RPL_353_NAMREPLY(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 353 " + client.get_nickname() + " = " + channel.get_name() + " :" + channel.get_clients());
}

/*
RPL_366_ENDOFNAMES (366)
  "<client> <channel> :End of /NAMES list"
Sent as a reply to the NAMES command, this numeric specifies the end of a list of channel member names.
*/
void RPL_366_ENDOFNAMES(Client & client, Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 366 " + client.get_nickname() + " " + channel.get_name() + " :End of /NAMES list");
}
