/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 17:37:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "Server.hpp"

Nick::Nick() : Command("NICK")
{}

Nick::~Nick()
{}

void Nick::exec(Client & client, const Params & params, Server & server)
{
	if (!client.is_hasPass())
		ERR_NOTREGISTERED(client, server);

	if (params.get_nbr() < 1)
		ERR_NONICKNAMEGIVEN(client);

	if (params.get_first().length() > 9)
		ERR_ERRONEUSNICKNAME(client, params.get_first());

	for (int i = server.get_nbr_connected(); i > 0; --i)
	{
		if (server.get_client(i)->get_nickname() == params.get_first())
			ERR_NICKNAMEINUSE(client, params.get_first());
	}

	client.set_nickname(params.get_first());

	if (client.is_registed())
		RPL_WELCOME(client, server);
}
