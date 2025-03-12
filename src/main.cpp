/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 16:27:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <unistd.h>
#include "server.hpp"
#include "utils.hpp"
#include "ServerException.hpp"

static int convert_port(const char * str)
{
	char *		endptr = NULL;
	long int	nbr = strtol(str, &endptr, 10);
	if (*endptr != '\0')
		throw (std::runtime_error(RED "bad argument!" RESET));
	if (nbr < 0 || nbr > 65535)
		throw (std::runtime_error(RED "port must be between 0 65535" RESET));
	return (nbr);
}

static void	check_arg(int argc)
{
	if (argc != 3)
	{
		std::cerr << RED "wrong number argument !" RESET << std::endl;
		std::cerr << YELLOW "usage :" RESET << std::endl;
		throw (std::runtime_error(YELLOW "./ircserv <port> <password>" RESET));
	}
}

int main(int argc, char **argv)
{
	try
	{
		check_arg(argc);
		int port = convert_port(argv[1]);
		std::string password(argv[2]);
		int server = create_server(port);
		run_server(server, port, password);
		close(server);
	}
	catch (const ServerException& e)
	{
		close(e.getFd());
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
