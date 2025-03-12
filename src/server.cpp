/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 13:17:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "server.hpp"

int create_server(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (sock == -1)
		throw(std::runtime_error(RED "socket init failed" RESET));

	std::cout	<< BLUE "create server on port " RESET << port << std::endl;
	return (sock);
}

void run_server(const int server, const int port, const std::string & password)
{
	std::cout	<< BLUE "run server " RESET << server
				<< BLUE " on port " RESET << port
				<< BLUE " with password " RESET << password << std::endl;
}
