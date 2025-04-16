/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meteobot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:47:23 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/16 20:07:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <exception>
#include <iostream>
#include "signal.hpp"
#include "utils.hpp"
#include "Bot.hpp"

volatile sig_atomic_t g_sigint;

int main(int argc, char ** argv)
{
	try
	{
		sigint_handler_setup();
		check_nbr_arg(argc, argv);
		Bot bot(str_to_port(argv[1]), std::string(argv[2]));
		bot.authentication();
		bot.run();
		return (EXIT_SUCCESS);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (EXIT_FAILURE);
	}
}
