/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:04:21 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/29 01:51:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.hpp"

void log(const std::string & msg)
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
	log(fd_log(fd) + " " + to_string_left(action, 7, ' ') + ": " RESET + msg);
}

void log_server(int fd, const std::string & msg)
{
	log(fd_log(fd) + " " + FG_YELLOW + msg + RESET);
}

void log_channel(const std::string & channel_name, const std::string & action, const std::string & who)
{
	log(FG_YELLOW "channel " RESET + channel_name + FG_YELLOW " : " + action + " " RESET + who);
}
