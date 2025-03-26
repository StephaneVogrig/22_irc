/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 16:22:57 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

void RPL_WELCOME(Client & client, Server & server);
void RPL_TOPIC(Client & client, Channel & channel);
void RPL_TOPICWHOTIME(Client & client, Channel & channel);
void RPL_NAMREPLY(Client & client, Channel & channel);
void RPL_ENDOFNAMES(Client & client, Channel & channel);

#endif