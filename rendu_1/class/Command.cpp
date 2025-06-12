/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:15 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/09 17:08:01 by svogrig          ###   ########.fr       */
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
