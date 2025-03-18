/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 17:25:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNick.hpp"

CmdNick::CmdNick() : Command("NICK")
{
}

CmdNick::~CmdNick()
{
}

void CmdNick::exec(const std::string & arg)
{
	std::cout << PURPLE "this command is NICK" RESET << std::endl;
	std::cout << PURPLE "arg = " RESET << arg  << std::endl;
}
