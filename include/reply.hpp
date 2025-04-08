/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 13:20:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"

/*
RPL_TOPIC (332)
  "<client> <channel> :<topic>"
Sent to a client when joining the <channel> to inform them of the current topic of the channel.
*/
/*332*/ # define RPL_332_TOPIC_(nickname, channel_name, channel_topic) ":server 332 " + nickname + " " + channel_name + " :" + channel_topic

class Server;

void RPL_001_WELCOME(Client & client, Server & server);
void RPL_315_ENDOFWHO(Client & client);
void RPL_318_ENDOFWHOIS(Client & client, const std::string & name);
void RPL_324_CHANNELMODEIS(const Client & client, const Channel & channel, Server & server);
void RPL_329_CREATIONTIME(const Client & client, const Channel & channel, Server & server);
void RPL_331_NOTOPIC(Client & client, Channel & channel);
void RPL_332_TOPIC(Client & client, Channel & channel);
void RPL_333_TOPICWHOTIME(Client & client, Channel & channel);
void RPL_341_INVITING(Client & client, const std::string & name, Channel & channel);
void RPL_352_WHOREPLY(Client & client, Client & target, Server & server, const std::string & channel_name, const std::string & flags);
void RPL_353_NAMREPLY(Client & client, Channel & channel);
void RPL_366_ENDOFNAMES(Client & client, Channel & channel);

#endif