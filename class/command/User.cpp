/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 16:22:04 by gcannaud         ###   ########.fr       */
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
    {
        ERR_NOTREGISTERED(client, server);
        return ;
    }
	if (client.is_registed())
	{
		ERR_ALREADYREGISTRED(client);
		return ;
	}
	if (params.get_nbr() < 4)
	{
		ERR_NEEDMOREPARAMS(client, "USER");
		return ;
	}
	client.set_username(params.get_first());
	client.set_realname(params.get_param(params.get_nbr() - 1));
	if (client.is_registed())
		RPL_WELCOME(client, server);
}
