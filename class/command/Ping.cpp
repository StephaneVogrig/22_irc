/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/25 21:35:27 by svogrig          ###   ########.fr       */
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

void Ping::exec(Client * client, const Params & params, Server & Server)
{
    (void)Server;
    if (!client->is_registed())
    {
        if (send(client->get_fd(), ":server 451 * :You need to register first\r\n", 44, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    if (params.get_param(0).empty())
    {
        if (send(client->get_fd(), ":server 461 * :Not enough parameters\r\n", 36, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    std::string response = "PONG :" + params.get_param(0) + "\r\n";
    if (send(client->get_fd(), response.c_str(), response.size(), 0) == -1)
        throw(std::runtime_error("send failed"));
}
