/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/19 14:22:03 by svogrig          ###   ########.fr       */
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

void User::exec(Client * client, const std::string & arg, const Server & Server)
{
    (void)Server;
    if (client->get_username() != "*")
        return ;
    client->set_username(arg);
	std::cout << PURPLE "new user name is " RESET << client->get_username() << std::endl;
    // if (client->get_nickname() != "*")
    // {
    //     client->registed();
    //     std::cout << PURPLE "client as registed !" RESET << std::endl;
    //     std::string msg;
    //     msg = client->get_nickname() + " :Welcome to the " + "best irc server" + " Network, ";
    // 	std::cout << msg << std::endl;
	// 	if (send(client->get_fd(), msg.c_str(), msg.length(), 0) == -1)
    //         throw(std::runtime_error("send failed"));
    // }
}
