/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 20:08:18 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdUser.hpp"
#include "Server.hpp"

CmdUser::CmdUser() : Command("USER")
{
}

CmdUser::~CmdUser()
{
}

void CmdUser::exec(Client * client, const std::string & arg, const Server & Server)
{
    (void)client;

	std::cout << Server.get_client(2) << std::endl;
	std::cout << PURPLE "this command is USER" RESET << std::endl;
	std::cout << PURPLE "arg = " RESET << arg  << std::endl;

}
