/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/01 21:28:57 by svogrig          ###   ########.fr       */
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
    client.quit_all_channels();
    std::string msg = client.get_nickname() + " :Goodbye";
	client.send_msg(msg);
    // if (send(client.get_fd(),  msg.c_str(), msg.length(), 0) == -1)
    //     throw(std::runtime_error("send failed"));
    client.set_kicked(true);
}
