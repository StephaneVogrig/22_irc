/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 00:24:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

/*001*/ void RPL_WELCOME(Client & client, Server & server);
/*331*/ void RPL_NOTOPIC(Client & client, Channel & channel);
/*332*/ void RPL_TOPIC(Client & client, Channel & channel);
/*333*/ void RPL_TOPICWHOTIME(Client & client, Channel & channel);
/*353*/ void RPL_NAMREPLY(Client & client, Channel & channel);
/*366*/ void RPL_ENDOFNAMES(Client & client, Channel & channel);

#endif