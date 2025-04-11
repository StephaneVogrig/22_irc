/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/11 15:38:53 by gcannaud         ###   ########.fr       */
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
    if (params.get_nbr() < 1)
        ERR_461_NEEDMOREPARAMS(client, "PING", server);

    client.send_msg(":" + server.get_name() + " PONG " + server.get_name() + " :" + params.get_first());
}
