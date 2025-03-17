/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:21 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/17 20:45:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <string>

class User
{
	public:

		User(const std::string & userName, const std::string & nickName);
		User(const User & toCopy);
		~User();

		User & operator = (const User & toAssign);

	private:

		std::string _userName;
		std::string _realName;
		std::string _nickName;

};

#endif