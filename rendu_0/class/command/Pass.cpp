/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 14:22:48 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "Server.hpp"

Pass::Pass() : Command("PASS")
{}

Pass::~Pass()
{}

void Pass::exec(Client & client, const Params & params, Server & server)
{
	if (!server.get_password().empty() && params.get_nbr() < 1)
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	if (server.get_password().empty() || client.is_hasPass())
		ERR_462_ALREADYREGISTRED(client, server);

	if (!server.get_password().empty() && params.get_param(0) != server.get_password())
		ERR_464_PASSWDMISMATCH(client, server);

	client.set_hasPass(true);
}
