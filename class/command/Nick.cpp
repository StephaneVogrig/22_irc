/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/02 17:09:56 by gcannaud         ###   ########.fr       */
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
		ERR_NEEDMOREPARAMS(client, "NICK");
	if (params.get_first().empty())
		ERR_NONICKNAMEGIVEN(client);
	if (params.get_first().length() > 9)
		ERR_ERRONEUSNICKNAME(client, params.get_first());
	if (Channel::is_a_valid_name(params.get_first()) || params.get_first()[0] == '@' || params.get_first()[0] == '#' || params.get_first()[0] == ':' || params.get_first()[0] == '+' || params.get_first()[0] == '!' || params.get_first().find_first_of(" ") != std::string::npos)
		ERR_ERRONEUSNICKNAME(client, params.get_first());
	for (int i = server.get_nbr_connected(); i > 0; --i)
	{
		if (server.get_client_by_idx(i)->get_nickname() == params.get_first())
			ERR_NICKNAMEINUSE(client, params.get_first());
	}
	if (client.is_registed())
	{
		std::string oldnam = client.get_nickname();
		client.set_nickname(params.get_first());
		client.send_msg(":" + oldnam + " NICK " + params.get_first());
	}
	else
	{
		client.set_nickname(params.get_first());
		if (client.is_registed())
			RPL_WELCOME(client, server);
	}
}
