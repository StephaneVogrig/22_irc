/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:13:59 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/25 18:33:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(const std::string & str)
{
	extract_info(str);
}

Message::Message(const Message & toCopy)
{
	*this = toCopy;
}

Message::~Message()
{}

Message & Message::operator = (const Message & toAssign)
{
	if (this == &toAssign)
		return *this;
	_prefix = toAssign._prefix;
	_command = toAssign._command;
	_parameters = toAssign._parameters;
	
	return *this;
}

const std::string & Message::getPrefix()
{
	return (_prefix);
}

const std::string & Message::getCommand()
{
	return (_command);
}

std::vector<std::string> & Message::getParameters()
{
	return (_parameters);
}

void Message::extract_command(const std::string & str, size_t start, size_t stop)
{
	_command = str.substr(start, stop - start);
	for(std::string::iterator it = _command.begin(); it <= _command.end(); ++it)
		*it = std::toupper(*it);
}

void Message::extract_info(const std::string & str)
{
	size_t start = 0;
	size_t stop = 0;
	
	/* prefix */
	if (str[0] == ':')
	{
		stop = str.find(' ', 0);
		if (stop == std::string::npos)
		{
			_prefix = str.substr(1, str.length() - 1);
			return ;
		}
		_prefix = str.substr(1, stop - 1);
		start = stop + 1;
	}

	/* command */
	stop = str.find(' ', start);
	if (stop == std::string::npos)
	{
		extract_command(str, start, str.length());
		return ;
	}
	extract_command(str, start, stop);
	start = stop + 1;

	/* parameters */
	stop = str.find(' ', start);
	int nbr_param = 0;
	while (stop != std::string::npos && nbr_param < 14)
	{
		if (str[start] == ':')
		{
			start++;
			break ;
		}
		_parameters.push_back(str.substr(start, stop - start));
		start = stop + 1;
		stop = str.find(' ', start);
		nbr_param++;
	}
	if (start < str.length())
		_parameters.push_back(str.substr(start, str.length() - start));
}
