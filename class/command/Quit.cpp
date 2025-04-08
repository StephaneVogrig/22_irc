/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/08 13:48:36 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"
#include "Server.hpp"

Quit::Quit() : Command("QUIT")
{
}

Quit::~Quit()
{
}

void Quit::exec(Client & client, const Params & params, Server & server)
{
	std::string msg;
	try
	{
		if (params.get_nbr() > 1)
			ERR_461_NEEDMOREPARAMS(client, _name);
		if (params.get_nbr() == 1)
			msg = params.get_param(0);
		if (params.get_nbr() == 1 && msg.empty())
			ERR_412_NOTEXTTOSEND(client);
	}
	catch(const Protocole_error& e)
	{}

	client.send_msg_all_channels(server, msg);
	client.send_msg(":" + client.get_nickname() + " QUIT :" + msg);
	client.set_kicked(true);
}
