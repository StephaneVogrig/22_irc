/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 14:19:42 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"
#include "Server.hpp"

Ping::Ping() : Command("PING")
{
}

Ping::~Ping()
{
}

void Ping::exec(Client & client, const Params & params, Server & Server)
{
    (void)Server;
    if (!client.is_registed())
    {
        ERR_NOTREGISTERED(client);
        return;
    }
    if (params.get_nbr() < 1)
    {
        ERR_NEEDMOREPARAMS(client, "PING");
        return;
    }
    std::string response = ": PONG :" + params.get_first() + "\r\n";
    if (send(client.get_fd(), response.c_str(), response.size(), 0) == -1)
        throw(std::runtime_error("send failed"));
}
