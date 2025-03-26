/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 14:48:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "Server.hpp"
#include "utils.hpp"

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

void sig_handler(int sig)
{
	g_signal = sig;
	std::cout << PURPLE " : signal recut : " RESET << sig << std::endl;
}

int main(int argc, char **argv)
{
	signal(SIGINT, sig_handler);
	try
	{
		check_arg(argc);
		int port = convert_port(argv[1]);
		std::string password(argv[2]);
		Server server(port, password, "GreatServer_42");
		server.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
