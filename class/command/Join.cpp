/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:03 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/20 19:49:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join(void) : Command("JOIN")
{}

Join::~Join(void)
{}

void Join::exec(Client * client, const std::string & param, Server & server)
{
	if (!server.channel_exist(param))
		server.create_channel(param);
	Channel * channel = server.get_channel(param);
	std::cout << client->get_nickname() << " join channel " << channel->get_name()
			<< " ptr: " << channel << std::endl;
	(void)client;
	
}