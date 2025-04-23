/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:13:59 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/28 21:14:00 by svogrig          ###   ########.fr       */
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


std::ostream & operator << (std::ostream & os, const Message & msg)
{
	os << FG_BLUE "prefix: " RESET;
	msg.get_prefix().empty()		? os << "<empty>" : os << msg.get_prefix();

	os << FG_BLUE " command: " RESET;
	msg.get_command().empty()		? os << "<empty>" : os << msg.get_command();

	os << FG_BLUE " params: " RESET;
	msg.get_params().get_nbr() == 0 ? os << "<empty>" : os << msg.get_params();

	return os;
}

const std::string & Message::get_prefix() const
{
	return _prefix;
}

const std::string & Message::get_command() const
{
	return _command;
}

const Params & Message::get_params() const
{
	return _parameters;
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
	Params params(str.substr(start, str.length() - start));
	_parameters = params;

}
