/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:15 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/18 16:18:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

typedef void (*t_mbrFuncPtr)(const std::string & params);

std::string cmd_list[] = {"JOIN", "NICK"};

Command::Command(const std::string & str)
{
	
	int pos = str.find(' ');
	std::string cmd = str.substr(0, pos);
	std::string param = str.substr(pos + 1, str.length());
	for(std::string::iterator it = cmd.begin(); it <= cmd.end(); ++it)
		*it = std::toupper(*it);
}
Command::~Command()
{}

void join(const std::string & params)
{}
void nick(const std::string & params)
{}

t_mbrFuncPtr func[] = {&join(), &nick(std::string &)};