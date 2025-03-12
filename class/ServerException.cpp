/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:51:06 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 17:46:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerException.hpp"
#include "utils.hpp"

ServerException::ServerException(const std::string & msg, int fd) : _msg(msg), _fd(fd)
{
	_msg = RED + _msg + RESET;
}

ServerException::~ServerException() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
}

int ServerException::getFd() const
{
	return _fd;
}

const char * ServerException::what() const throw()
{
	return _msg.c_str();
}
