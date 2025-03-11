/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 17:10:31 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <iostream>

#define FAILURE 0
#define SUCCESS 1

int	check_arg(int argc, char **argv)
{
	(void) argv;
	if (argc != 3)
	{
		std::cerr << "wrong number argument !" << std::endl;
		std::cerr << "usage :" << std::endl;
		std::cerr << "./ircserv <port> <password>" << std::endl;
		return (FAILURE);
	}
	
	int	port = atoi(argv[1]);
	if (port < 0 || port > 65535)
	{
		std::cerr << "port must be between 0 65535" << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (!check_arg(argc, argv))
		return (EXIT_FAILURE);
	std::cout << "hello ircserv" << std::endl;
	return (EXIT_SUCCESS);
}
