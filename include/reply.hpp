/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:45:53 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/21 19:45:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
#define REPLY_HPP

# include "Client.hpp"
# include "Channel.hpp"

void rpl_topic(Client & client, Channel & channel);
void rpl_topicwhotime(Client & client, Channel & channel);
void rpl_namereply(Client & client, Channel & channel);
void rpl_endofnames(Client & client, Channel & channel);

#endif