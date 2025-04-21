/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 20:38:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Server.hpp"

#include "signal.hpp"
#include "utils.hpp"

int main(int argc, char ** argv)
{
	try
	{
		sigint_handler_setup();
		check_nbr_arg(argc, argv);
		Server server(str_to_port(argv[1]), std::string(argv[2]), "GreatServer_42");
		server.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << FG_RED << e.what() << RESET << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
