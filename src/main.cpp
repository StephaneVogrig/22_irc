/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 18:00:25 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <iostream>

int convert_port(const char * str)
{
	char *		endptr = NULL;
	long int	nbr = strtol(str, &endptr, 10);
	if (*endptr != '\0')
		throw (std::runtime_error("bad argument!"));
	if (nbr < 0 || nbr > 65535)
		throw (std::runtime_error("port must be between 0 65535"));
	return (nbr);
}

void	check_arg(int argc)
{
	if (argc != 3)
	{
		std::cerr << "wrong number argument !" << std::endl;
		std::cerr << "usage :" << std::endl;
		std::cerr << "./ircserv <port> <password>" << std::endl;
		throw (std::runtime_error(""));
	}
}

int main(int argc, char **argv)
{
	try
	{
		check_arg(argc);
		int port = convert_port(argv[1]);
		(void)port;
		std::cout << "hello ircserv" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
