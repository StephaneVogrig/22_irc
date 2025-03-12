/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:55 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/12 15:42:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEREXCEPTION_HPP
# define SERVEREXCEPTION_HPP

# include <iostream>
# include <exception>

class ServerException : public std::exception
{
	public :
		ServerException(const std::string & msg, int fd);
		~ServerException() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;

		int getFd() const;

		const char * what() const throw();

	protected :

		std::string _msg;
		int			_fd;

};


#endif