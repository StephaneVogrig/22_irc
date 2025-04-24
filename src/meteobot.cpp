/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meteobot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:47:23 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 16:19:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <exception>
#include <iostream>
#include "signal.hpp"
#include "utils.hpp"
#include "Bot.hpp"
#include "settings.hpp"

int main(int argc, char ** argv)
{
	try
	{
		sigint_handler_setup();
		if (argc != 4)
		{
			std::cerr << FG_RED"wrong number argument !" RESET << std::endl;
			std::cerr << FG_YELLOW"usage :" RESET << std::endl;
			throw (std::runtime_error(FG_YELLOW + std::string(argv[0]) + " <ipv4> <port> <password>" RESET));
		}
		std::string ip(argv[1]);
		if (ip[0] == '\0')
			ip = IP_DEFAULT;
		Bot bot(ip, str_to_port(argv[2]), std::string(argv[3]));
		bot.authentication();
		bot.run();
		return (EXIT_SUCCESS);
	}
	catch(const std::exception& e)
	{
		std::cerr << FG_RED << e.what() << FG_DEFAULT << '\n';
		return (EXIT_FAILURE);
	}
}
