/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:51:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/17 18:00:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(const std::string & userName, const std::string & nickName)
	: _userName(userName), _nickName(nickName)
{}

User::User(const User & toCopy)
{
	*this = toCopy;
}

User::~User()
{}

User & User::operator = (const User & toAssign)
{
	if (this == &toAssign)
		return ;
	_userName = toAssign._userName;
	_nickName = toAssign._nickName;
	return *this;
}
