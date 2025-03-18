/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 20:26:24 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNick.hpp"
#include "Server.hpp"

CmdNick::CmdNick() : Command("NICK")
{
}

CmdNick::~CmdNick()
{
}

void CmdNick::exec(Client * client, const std::string & arg, const Server & Server)
{
    (void)Server;
    client->set_nickname(arg);
	std::cout << PURPLE "new nick name is " RESET << client->get_nickname() << std::endl;
}
