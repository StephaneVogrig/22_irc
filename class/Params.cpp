/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Params.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:04:23 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/02 15:04:53 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Params.hpp"

#include "log.hpp"

Params::Params()
{}

Params::Params(const std::string & str)
{
	size_t start = str.find_first_not_of(' ', 0);
	if (str[start] == ':')
		start++;
	else
	{
		size_t stop = str.find(' ', start);
		int nbr_param = 0;
		while (stop != std::string::npos && nbr_param < 14)
		{
			_params.push_back(str.substr(start, stop - start));
			start = str.find_first_not_of(' ', stop);
			if (str[start] == ':')
			{
				start++;
				break ;
			}
			stop = str.find(' ', start);
			nbr_param++;
		}
	}
	if (start <= str.length())
		_params.push_back(str.substr(start, str.length() - start));
}

Params::Params(const Params & to_copy)
{
	*this = to_copy;
}

Params::~Params()
{}

Params & Params::operator = (const Params & to_assign)
{
	if (this == &to_assign)
		return *this;
	_params = to_assign._params;
	return *this;
}

std::ostream & operator << (std::ostream & os, const Params & params)
{
	for (int i = 0; i < params.get_nbr(); ++i)
	{
		if (i != 0)
			os << FG_BLUE " | " RESET;
		os << params.get_param(i);
	}
	return os;
}

int	Params::get_nbr() const
{
	return _params.size();
}

const std::string &	Params::get_param(int idx) const
{
	return _params[idx];
}

const std::string &	Params::get_first() const
{
	return _params[0];
}
