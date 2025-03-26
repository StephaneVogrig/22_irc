/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:42:10 by gcannaud         ###   ########.fr       */
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
        //462
        return ;
    }
    if (!Server.get_password().empty() && params.get_param(0).empty())
    {
        //461
        return ;
    }
    if (!Server.get_password().empty() && params.get_param(0) != Server.get_password())
    {
        if (send(client.get_fd(), ":server 464 * :Password incorrect\r\n", 37, 0) == -1)
            throw(std::runtime_error("send failed"));
        client.set_kicked(true);
        return;
        return ;
    }
    client.set_hasPass(true);
}