/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/31 17:37:56 by gcannaud         ###   ########.fr       */
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
    if (client.is_hasPass())
        ERR_ALREADYREGISTRED(client);

    if (!server.get_password().empty() && params.get_nbr() < 1)
        ERR_NEEDMOREPARAMS(client, "PASS");

    if (!server.get_password().empty() && params.get_param(0) != server.get_password())
        ERR_PASSWDMISMATCH(client);

    client.set_hasPass(true);
}
