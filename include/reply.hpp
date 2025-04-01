/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/01 18:54:35 by svogrig          ###   ########.fr       */
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
/*332*/ # define RPL_TOPIC_(nickname, channel_name, channel_topic) ":server 332 " + nickname + " " + channel_name + " :" + channel_topic

class Server;

/*001*/ void RPL_WELCOME(Client & client, Server & server);
/*324*/ void RPL_CHANNELMODEIS(const Client & client, const Channel & channel);
/*331*/ void RPL_NOTOPIC(Client & client, Channel & channel);
/*332*/ void RPL_TOPIC(Client & client, Channel & channel);
/*333*/ void RPL_TOPICWHOTIME(Client & client, Channel & channel);
/*341*/ void RPL_INVITING(Client & client, const std::string & name, Channel & channel);
/*353*/ void RPL_NAMREPLY(Client & client, Channel & channel);
/*366*/ void RPL_ENDOFNAMES(Client & client, Channel & channel);

#endif