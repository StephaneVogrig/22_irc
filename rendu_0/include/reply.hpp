/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 18:50:59 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

void RPL_001_WELCOME(Client & client, Server & server);
void RPL_002_YOURHOST(Client & client, Server & server);
void RPL_003_CREATED(Client & client, Server & server);
void RPL_004_MYINFO(Client & client, Server & server);
void RPL_315_ENDOFWHO(Client & client, Server & server);
void RPL_322_LIST(Client & client, Channel & channel, Server & server);
void RPL_323_LISTEND(Client & client, Server & server);
void RPL_324_CHANNELMODEIS(Client & client, Channel & channel, Server & server);
void RPL_329_CREATIONTIME(Client & client, const Channel & channel, Server & server);
void RPL_331_NOTOPIC(Client & client, Channel & channel, Server & server);
void RPL_332_TOPIC(Client & client, Channel & channel, Server & server);
void RPL_333_TOPICWHOTIME(Client & client, Channel & channel, Server & server);
void RPL_341_INVITING(Client & client, const std::string & name, Channel & channel, Server & server);
void RPL_352_WHOREPLY(Client & client, Client & target, Server & server, Channel * channel);
void RPL_353_NAMREPLY(Client & client, Channel & channel, Server & server);
void RPL_366_ENDOFNAMES(Client & client, Channel & channel, Server & server);

#endif