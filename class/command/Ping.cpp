/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:17:45 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

Ping::Ping() : Command("PING")
{}

Ping::~Ping()
{}

void Ping::exec(Client & client, const Params & params, Server & server)
{
    if (params.get_nbr() < 1)
        ERR_461_NEEDMOREPARAMS(client, _name, server);

    client.send_msg(":" + server.get_name() + " PONG " + server.get_name() + " :" + params.get_first());
}
