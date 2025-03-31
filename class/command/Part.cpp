/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:47:39 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/31 19:54:19 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"
#include "Server.hpp"

Part::Part() : Command("PART")
{}

Part::~Part()
{}

void Part::exec(Client & client, const Params & params, Server & server)
{
    if (!client.is_registed())
        ERR_NOTREGISTERED(client, server);
    if (params.get_nbr() < 2)
    {
        ERR_NEEDMOREPARAMS(client, "PART");
    }
    Elements channels(params.get_first());
    std::string arg;
    if (params.get_nbr() >= 2)
        arg = params.get_param(1);
    for(int i = channels.get_nbr(); i > 0; --i)
    {
        try
        {
            Channel * channel = server.get_channel(channels.get_element(i - 1));
            if (!channel->is_join(client))
                ERR_NOTONCHANNEL(client, *channel);
            channel->remove_client(client);
            client.send_msg(":" + client.get_nickname() + " PART " + channel->get_name() + " " + arg);
        }
        catch (const Server::Channel_not_found & e)
        {
            ERR_NOSUCHCHANNEL(client, channels.get_first());
        }
        catch (const Protocole_error &e)
        {}
    }
}
