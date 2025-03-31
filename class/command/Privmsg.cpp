/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/31 13:01:01 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"
#include "Server.hpp"

Privmsg::Privmsg() : Command("Privmsg")
{
}

Privmsg::~Privmsg()
{
}

void Privmsg::exec(Client & client, const Params & params, Server & server)
{
    if (!client.is_registed())
        ERR_NOTREGISTERED(client, server);
    if (params.get_nbr() < 2)
        ERR_NEEDMOREPARAMS(client, "PRIVMSG");

    const std::string & target = params.get_first();
    const std::string & message = params.get_param(1);
    if (target[0] == '#' || target[0] == '&')
    {
        if (!server.channel_exist(target))
            ERR_NOSUCHCHANNEL(client, target);
        
        Channel & channel = server.get_channel(target);
        
        /*if (!channel.is_client(client))
            ERR_CANNOTSENDTOCHAN(client, target);*/

        channel.send_msg(client, message);
    }
    else
    {
        int i;
        for (i = server.get_nbr_connected(); i > 0; --i)
	    {
		    if (server.get_client(i)->get_nickname() == target)
                break;
	    }
        if (i == 0)
            ERR_NOSUCHNICK(client, server, target);
        server.get_client(i)->send_msg(":" + client.get_nickname() + " PRIVMSG " + target + " :" + message);
    }
}
