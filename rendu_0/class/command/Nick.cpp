/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 18:07:25 by gcannaud         ###   ########.fr       */
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
	if (!server.get_password().empty() && !client.is_hasPass())
		ERR_451_NOTREGISTERED(client, server);

	if (params.get_nbr() == 0)
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	const std::string & nickname = params.get_first();

	if (nickname.empty())
		ERR_431_NONICKNAMEGIVEN(client, server);

	if (nickname.length() > 9)
		ERR_432_ERRONEUSNICKNAME(client, nickname, server);

	if (!Client::is_a_valid_nickname(nickname))
		ERR_432_ERRONEUSNICKNAME(client, nickname, server);

	if (server.get_client_by_name(nickname) != NULL)
		ERR_433_NICKNAMEINUSE(client, nickname, server);

	if (client.is_registed())
	{
		std::string oldnam = client.get_nickname();
		client.send_on_all_channels(_name + " " + nickname);
		client.set_nickname(nickname);
	}
	else
	{
		client.set_nickname(nickname);
		if (client.is_registed())
			server.rpl_accept(client);
	}
}
