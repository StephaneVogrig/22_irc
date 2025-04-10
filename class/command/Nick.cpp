/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:43:26 by svogrig          ###   ########.fr       */
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
		ERR_451_NOTREGISTERED(client, server);

	if (params.get_nbr() == 0)
		ERR_461_NEEDMOREPARAMS(client, "NICK", server);

	const std::string & nickname = params.get_first();

	if (nickname.empty())
		ERR_431_NONICKNAMEGIVEN(client, server);

	if (nickname.length() > 9)
		ERR_432_ERRONEUSNICKNAME(client, nickname, server);

	if (Channel::is_a_valid_name(nickname) || nickname[0] == '@' || nickname[0] == '#' || nickname[0] == ':' || nickname[0] == '+' || nickname[0] == '!' || nickname.find_first_of(" ") != std::string::npos)
		ERR_432_ERRONEUSNICKNAME(client, nickname, server);

	if (server.get_client_by_name(nickname) != NULL)
		ERR_433_NICKNAMEINUSE(client, nickname, server);

	if (client.is_registed())
	{
		std::string oldnam = client.get_nickname();
		client.set_nickname(nickname);
		client.send_msg(":" + oldnam + " NICK " + nickname);
	}
	else
	{
		client.set_nickname(nickname);
		if (client.is_registed())
			RPL_001_WELCOME(client, server);
	}
}
