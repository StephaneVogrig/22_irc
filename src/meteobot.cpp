/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meteobot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:47:23 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 21:24:56 by svogrig          ###   ########.fr       */
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
	int exit_code = EXIT_SUCCESS;
	try
	{
		sigint_handler_setup();
		if (argc != 4)
		{
			std::cerr << FG_RED "wrong number argument !" RESET << std::endl;
			std::cerr << FG_YELLOW "usage :" RESET << std::endl;
			std::cerr << FG_YELLOW << std::string(argv[0]) << " <ipv4> <port> <password>" RESET << std::endl;
			return EXIT_FAILURE;
		}
		std::string ip(argv[1]);
		if (ip[0] == '\0')
			ip = IP_DEFAULT;
		Bot bot(ip, str_to_port(argv[2]), std::string(argv[3]));
		bot.authentication();
		bot.run();
	}
	catch(const Bot::Close & e)
	{}
	catch(const std::exception& e)
	{
		log_(FG_RED + std::string(e.what()) + FG_DEFAULT);
		exit_code = EXIT_FAILURE;
	}
	log_(FG_PURPLE BLINK_ON "Bot closed" RESET);
	return exit_code;
}
