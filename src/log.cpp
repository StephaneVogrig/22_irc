/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:04:21 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 17:47:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.hpp"

void log_(const std::string & msg)
{
	std::cout << "\r" ERASE_LINE FG_PURPLE "[" << current_time_str() << "] " RESET
	<< msg << std::endl;
}

std::string fd_log(int fd)
{
	return FG_PURPLE "[" RESET + to_string(fd) + FG_PURPLE "]";
}

void log_msg(int fd, const std::string & action, const std::string & msg)
{
	log_(fd_log(fd) + " " + to_string_left(action, 7, ' ') + " " + msg + RESET);
}

void log_server(int fd, const std::string & msg)
{
	log_(fd_log(fd) + " " + FG_PURPLE + msg + RESET);
}
