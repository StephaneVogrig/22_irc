/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/27 19:55:34 by svogrig          ###   ########.fr       */
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

void Ping::exec(Client & client, const Params & params, Server & server)
{
    if (!client.is_registed())
        ERR_NOTREGISTERED(client, server);

    if (params.get_nbr() < 1)
        ERR_NEEDMOREPARAMS(client, "PING");

    client.send_msg(":" + server.get_name() + " PONG :" + params.get_first());
}
