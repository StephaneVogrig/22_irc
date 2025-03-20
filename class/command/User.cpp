/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/20 19:16:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"

User::User() : Command("USER")
{
}

User::~User()
{
}

void User::exec(Client * client, const std::string & arg, Server & Server)
{
	(void)Server;
    if (!client->is_hasPass())
    {
        if(send(client->get_fd(), ":server 451 * :You need to send PASS first\r\n", 44, 0) == -1)
			throw(std::runtime_error("send failed"));
        return;
    }
	if (arg.empty())
	{
		if(send(client->get_fd(), ":server 461 * :Not enough parameters\r\n", 36, 0) == -1)
			throw(std::runtime_error("send failed"));
		return;
	}
	client->set_username(arg);
	std::string msg;
    msg = ":server 001 " + client->get_nickname() + " :Welcome to the IRC Server\r\n";
	if (client->is_registed()) {
		if(send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
			throw(std::runtime_error("send failed"));
	}
}
