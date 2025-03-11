/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 17:45:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <iostream>

#define FAILURE 0
#define SUCCESS 1

int convert_port(const char * str)
{
	char *		endptr = NULL;
	long int	nbr = strtol(str, &endptr, 10);
	if (*endptr != '\0')
	{
		std::cerr << "bad argument!" << std::endl;
		return (INT_MAX);
	}
	if (nbr < 0 || nbr > 65535)
	{
		std::cerr << "port must be between 0 65535" << std::endl;
		return (INT_MAX);
	}
	return (nbr);
}

int	check_arg(int argc)
{
	if (argc != 3)
	{
		std::cerr << "wrong number argument !" << std::endl;
		std::cerr << "usage :" << std::endl;
		std::cerr << "./ircserv <port> <password>" << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (!check_arg(argc))
		return (EXIT_FAILURE);
	argv++;
	int port = convert_port(*argv);
	if (port == INT_MAX)
		return (EXIT_FAILURE);
	std::cout << "hello ircserv" << std::endl;
	return (EXIT_SUCCESS);
}
