/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 20:08:13 by gcannaud         ###   ########.fr       */
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
    (void)client;
	std::cout << Server.get_client(2) << std::endl;
	std::cout << PURPLE "this command is NICK" RESET << std::endl;
	std::cout << PURPLE "arg = " RESET << arg  << std::endl;
}
