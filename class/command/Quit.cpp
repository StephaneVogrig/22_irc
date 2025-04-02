/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/02 17:38:45 by gcannaud         ###   ########.fr       */
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
    (void) params;

    std::string msg;
    try
    {
        if (params.get_nbr() > 1)
            ERR_NEEDMOREPARAMS(client, "QUIT");
        if (params.get_nbr() == 1)
            msg = params.get_param(0);
        if (msg.empty())
            ERR_NOTEXTTOSEND(client);
    }
    catch(const Protocole_error& e)
    {
    }

    client.quit_serv_channels(msg);
	client.send_msg(":" + client.get_nickname() + " QUIT :" + msg);
    client.set_kicked(true);
}
