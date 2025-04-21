/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 19:56:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Server.hpp"

#include "signal.hpp"
#include "utils.hpp"

volatile sig_atomic_t g_sigint;

int main(int argc, char ** argv)
{
	try
	{
		signal(SIGINT, sigint_handler);
		check_nbr_arg(argc, argv);
		int port = str_to_port(argv[1]);
		Server server(port, std::string(argv[2]), "GreatServer_42");
		server.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << FG_RED << e.what() << RESET << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
