/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:12 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/17 21:29:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "utils.hpp"

Client::Client(int fd) : _fd(fd), _msg_buffer("")
{
}

Client::~Client()
{
}

void Client::receive_data(const std::string & data)
{
	std::string str = _msg_buffer + data;

	std::string delim("\r\n");
	size_t pos = str.find(delim);
	while (pos != std::string::npos)
	{
		std::string cmd = str.substr(0, pos);
		std::cout	<<  PURPLE "["  RESET << _fd << PURPLE "] : "  RESET
					<< cmd << std::endl;
		str.erase(0, pos + 2);
		pos = str.find(delim);
	}
	clear_msg_buffer();
	append_to_buffer(str);
}

const std::string & Client::get_msg_buffer(void) const
{
	return (_msg_buffer);
}

void Client::append_to_buffer(const std::string & str)
{
	_msg_buffer.append(str);
}

void Client::clear_msg_buffer(void)
{
	_msg_buffer.clear();
}

std::ostream & operator << (std::ostream & os, const Client & client)
{
	os << "client buffer: " << client.get_msg_buffer();
	return (os);
}
