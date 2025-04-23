/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Elements.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:26:29 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/12 18:59:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Elements.hpp"


#include "log.hpp"

Elements::Elements()
{}

Elements::Elements(const std::string & str)
{
	size_t start = 0;
	size_t stop = str.find(',', start);
	while (stop != std::string::npos)
	{
		_elements.push_back(str.substr(start, stop - start));
		start = stop + 1;
		stop = str.find(',', start);
	}
	if (start <= str.length())
		_elements.push_back(str.substr(start, str.length() - start));
}

Elements::Elements(const Elements & to_copy)
{
	*this = to_copy;
}

Elements::~Elements()
{}

Elements & Elements::operator = (const Elements & to_assign)
{
	if (this == &to_assign)
		return *this;
	_elements = to_assign._elements;
	return *this;
}

std::ostream & operator << (std::ostream & os, const Elements & elements)
{
	for (int i = 0; i < elements.get_nbr(); ++i)
	{
		if (i != 0)
			os << FG_BLUE " | " RESET;
		os << elements.get_element(i);
	}
	return os;
}

int	Elements::get_nbr() const
{
	return _elements.size();
}

const std::string &	Elements::get_element(int idx) const
{
	return _elements[idx];
}

const std::string &	Elements::get_first() const
{
	return _elements[0];
}
