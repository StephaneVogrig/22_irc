/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:19:31 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/16 20:00:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::time_t current_time_t()
{
	std::time_t rawtime;
	time (&rawtime);
	return (rawtime);
}

struct tm * current_time()
{
	std::time_t rawtime;
	time (&rawtime);
	return localtime(&rawtime);
}

std::string tm_to_time_str(struct tm * timeinfo)
{
	std::string str = to_string_right(timeinfo->tm_hour, 2, '0') + ":";
	str += to_string_right(timeinfo->tm_min, 2, '0') + ":";
	str += to_string_right(timeinfo->tm_sec, 2, '0');
	return str;
}

std::string current_time_str()
{
	return tm_to_time_str(current_time());
}

std::string current_date_str()
{
	struct tm * timeinfo = current_time();
	std::string str;
	str = to_string(timeinfo->tm_mon + 1) + "/";
	str = to_string_right(timeinfo->tm_mon + 1, 2, '0') + "/";
	str += to_string_right(timeinfo->tm_mday, 2, '0') + "/";
	str += to_string(timeinfo->tm_year + 1900);
	return str;
}

void check_nbr_arg(int argc, char ** argv)
{
	if (argc != 3)
	{
		std::cerr << FG_RED"wrong number argument !" RESET << std::endl;
		std::cerr << FG_YELLOW"usage :" RESET << std::endl;
		throw (std::runtime_error(FG_YELLOW + std::string(argv[0]) + " <port> <password>" RESET));
	}
}

int str_to_port(const char * str)
{
	char *		endptr = NULL;
	long int	nbr = strtol(str, &endptr, 10);
	if (*endptr != '\0')
		throw (std::runtime_error(FG_RED"bad argument!" RESET));
	if (nbr < 0 || nbr > 65535)
		throw (std::runtime_error(FG_RED"port must be between 0 65535" RESET));
	return (nbr);
}
