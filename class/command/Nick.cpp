/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:27:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"
#include "Server.hpp"

Nick::Nick() : Command("NICK")
{
}

Nick::~Nick()
{
}

void Nick::exec(Client & client, const Params & params, Server & Server)
{
    if (!client.is_hasPass())
    {
        if (send(client.get_fd(), ":server 451 * :You need to send PASS first\r\n", 44, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    if (params.get_param(0).empty() || params.get_param(0).length() > 9)
    {
        if (send(client.get_fd(), ":server 432 * :Erroneous nickname\r\n", 34, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    for (int i = Server.get_nbr_connected(); i > 0; --i)
	{
        if (Server.get_client(i)->get_nickname() == params.get_param(0))
        {
            std::string msg_err;
            msg_err = ":server 433 * " + params.get_param(0) + " :Nickname is already in use\r\n";
            if(send(client.get_fd(), msg_err.c_str(), msg_err.length(), 0) == -1)
                throw(std::runtime_error("send failed"));
            return;
        }
    }
    client.set_nickname(params.get_param(0));
    std::string msg;
    msg = ":server 001 " + client.get_nickname() + " :Welcome to the IRC Server\r\n";
    if (client.is_registed())
    {
        if (send(client.get_fd(), msg.c_str(), msg.length(), 0) == -1)
            throw(std::runtime_error("send failed"));
    }
}
