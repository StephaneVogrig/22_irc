/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:36:58 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:06:20 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"

List::List() : Command("LIST")
{}

List::~List()
{}

void List::exec(Client & client, const Params & params, Server & server)
{
	(void) params;
	server.send_channel_list(client);
}
