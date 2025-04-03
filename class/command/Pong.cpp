/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/03 17:24:58 by svogrig          ###   ########.fr       */
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

void Pong::exec(Client & client, const Params & params, Server & server)
{
	(void)server;

    if (params.get_param(0).empty()) {
        if (send(client.get_fd(), ":server 461 * PONG :Not enough parameters", 43, 0) == -1)
            throw(std::runtime_error("send failed"));
        return;
    }
    //client.update_last_pong();
}
