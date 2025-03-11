/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 18:07:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <iostream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define GREY "\033[37m"
#define RESET "\033[0m"
#define GREEN_BLINK	"\033[5;32m"

int convert_port(const char * str)
{
	char *		endptr = NULL;
	long int	nbr = strtol(str, &endptr, 10);
	if (*endptr != '\0')
		throw (std::runtime_error(RED "bad argument!" RESET));
	if (nbr < 0 || nbr > 65535)
		throw (std::runtime_error(RED "port must be between 0 65535" RESET));
	return (nbr);
}

void	check_arg(int argc)
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
		(void)port;
		std::cout << GREEN_BLINK "hello ircserv" RESET << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
