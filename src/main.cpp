/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/16 20:00:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "Server.hpp"
#include "utils.hpp"

void sig_handler(int sig)
{
	g_signal = sig;
}

int main(int argc, char ** argv)
{
	try
	{
		signal(SIGINT, sig_handler);
		check_nbr_arg(argc, argv);
		int port = str_to_port(argv[1]);
		std::string password(argv[2]);
		Server server(port, password, "GreatServer_42");
		server.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << FG_RED<< e.what() << RESET << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
