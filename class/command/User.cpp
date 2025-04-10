/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:48:14 by svogrig          ###   ########.fr       */
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

void User::exec(Client & client, const Params & params, Server & server)
{
	if (!client.is_hasPass())
		ERR_451_NOTREGISTERED(client, server);

	if (client.is_registed() || client.get_username() != "*")
		ERR_462_ALREADYREGISTRED(client, server);

	if (params.get_nbr() < 4)
		ERR_461_NEEDMOREPARAMS(client, "USER", server);

	client.set_username(params.get_first());
	client.set_realname(params.get_param(params.get_nbr() - 1));
	if (client.is_registed())
		RPL_001_WELCOME(client, server);
}
