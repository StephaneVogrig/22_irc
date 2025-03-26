/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:15 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 12:46:31 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"

Command::Command(const std::string & name) : _name(name)
{
}

Command::Command(const Command &to_cpy)
{
	*this = to_cpy;
}

Command & Command::operator=(const Command & to_assign)
{
	if (this == &to_assign)
		return *this;
	return *this;
}

Command::~Command()
{
}

void Command::exec(Client & client, const Params & params, Server & Server)
{
    (void)client;

	std::cout << Server.get_client(2) << std::endl;
	std::cout << PURPLE "this command is command" RESET << std::endl;
	std::cout << PURPLE "arg = " RESET << params  << std::endl;
}
