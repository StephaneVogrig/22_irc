/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:26:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"
#include "Server.hpp"

Quit::Quit() : Command("Quit")
{
}

Quit::~Quit()
{
}

void Quit::exec(Client & client, const Params & params, Server & Server)
{
    (void) Server;
    if (!client.is_registed())
    {
        if (send(client.get_fd(), ":server 451 * :You must be registered to quit\r\n", 48, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    // envoyé à tous les clients du serveur
    (void) params;
    std::string msg = client.get_nickname() + " :Goodbye\r\n";
    if (send(client.get_fd(),  msg.c_str(), msg.length(), 0) == -1)
        throw(std::runtime_error("send failed"));
    client.set_kicked(true);
}
