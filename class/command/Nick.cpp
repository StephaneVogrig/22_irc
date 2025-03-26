/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:03 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 14:12:16 by gcannaud         ###   ########.fr       */
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
        ERR_NOTREGISTERED(client);
        return;
    }
    if (params.get_nbr() < 1)
    {
        ERR_NONICKNAMEGIVEN(client);
        return;
    }
    if (params.get_first().length() > 9)
    {
        ERR_ERRONEUSNICKNAME(client, params.get_first());
        return;
    }
    for (int i = Server.get_nbr_connected(); i > 0; --i)
	{
        if (Server.get_client(i)->get_nickname() == params.get_first())
        {
            ERR_NICKNAMEINUSE(client, params.get_first());
            return;
        }
    }
    client.set_nickname(params.get_first());
    std::string msg;
    msg = ":server 001 " + client.get_nickname() + " :Welcome to the IRC Server\r\n";
    if (client.is_registed())
    {
        if (send(client.get_fd(), msg.c_str(), msg.length(), 0) == -1)
            throw(std::runtime_error("send failed"));
    }
}
