/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:16:49 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

Quit::Quit() : Command("QUIT")
{}

Quit::~Quit()
{}

void Quit::exec(Client & client, const Params & params, Server & server)
{
	std::string msg(_name);

	if (params.get_nbr() != 0)
		msg += " :" + params.get_first();

	client.quit_all_channels(server, msg);
	client.send_msg("ERROR :Connection closed");
	server.close_connection(client);
}
