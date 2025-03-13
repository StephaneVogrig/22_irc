/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/13 14:14:04 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_CPP
# define CLIENTS_CPP

# include <iostream>

class Clients
{
	public :
		Clients();
		~Clients();

	private :
		std::string _msg_buffer;

};

#endif