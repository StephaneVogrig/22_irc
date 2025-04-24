/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcExection.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:37:39 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 16:52:42 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOLE_ERROR_HPP
# define PROTOCOLE_ERROR_HPP

#include <exception>

class Protocole_error : public std::exception
{
	public:
		Protocole_error();
};

#endif
