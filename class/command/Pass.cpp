/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:55:55 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include "Server.hpp"

Pass::Pass() : Command("PASS")
{
}

Pass::~Pass()
{
}

void Pass::exec(Client & client, const Params & params, Server & Server)
{
    if (client.is_hasPass())
    {
        ERR_ALREADYREGISTRED(client);
        return ;
    }
    if (!Server.get_password().empty() && params.get_nbr() < 1)
    {
        ERR_NOTREGISTERED(client);
        return ;
    }
    if (!Server.get_password().empty() && params.get_param(0) != Server.get_password())
    {
        ERR_PASSWDMISMATCH(client);
        return ;
    }
    client.set_hasPass(true);
}
