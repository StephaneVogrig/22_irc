/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_rpl.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 03:28:55 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 19:30:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode_rpl.hpp"
#include "log.hpp"

Mode_rpl::Mode_rpl() : _current_action('\0')
{
	
}

Mode_rpl::Mode_rpl(const Mode_rpl & to_copy)
{
	*this = to_copy;
}

Mode_rpl::~Mode_rpl()
{}

Mode_rpl & Mode_rpl::operator = (const Mode_rpl & to_assign)
{
	if (this == &to_assign)
		return *this;
	_current_action = to_assign._current_action;
	_modes = to_assign._modes;
	_params = to_assign._params;
	return *this;
}

std::string Mode_rpl::get_mode_rpl()
{
	return _modes + _params;
}

bool Mode_rpl::is_empty()
{
	return _modes.empty();
}

void Mode_rpl::add_mode(char action, char mode, const std::string & param)
{
	if (action != _current_action)
	{
		_modes += action;
		_current_action = action;
	}
	_modes += mode;
	if (!param.empty())
		_params += " " + param;
}
