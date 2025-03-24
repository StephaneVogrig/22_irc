/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/19 14:22:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pong.hpp"
#include "Server.hpp"

Pong::Pong() : Command("Pong")
{
}

Pong::~Pong()
{
}

void Pong::exec(Client * client, const std::string & arg, Server & Server)
{
    (void)Server;
    if (!client->is_registed()) {
        if (send(client->get_fd(), ":server 451 * :You need to register first\r\n", 44, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    if (arg.empty()) {
        if (send(client->get_fd(), ":server 461 * PONG :Not enough parameters\r\n", 43, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    //client->update_last_pong();
}
