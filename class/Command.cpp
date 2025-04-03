/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:15 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/03 17:14:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"

Command::Command(const std::string & name) : _name(name)
{}

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
{}

const std::string & Command::get_name() const
{
	return _name;
}

void Command::exec(Client & client, const Params & params, Server & Server)
{
    (void)client;

	std::cout << Server.get_client_by_idx(2) << std::endl;
	std::cout << FG_PURPLE "this command is command" RESET << std::endl;
	std::cout << FG_PURPLE "arg = " RESET << params  << std::endl;
}
