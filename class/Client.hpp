/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 16:33:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CPP
# define CLIENT_CPP

# include <iostream>

class Client
{
	public :

		Client(int fd);
		~Client();

		const std::string & get_msg_buffer(void) const;
		int get_fd(void);

		// void receive_data(const std::string & data);
		void append_to_buffer(const std::string & str);
		void clear_msg_buffer(void);

	private :

		int			_fd;
		std::string _msg_buffer;

};

std::ostream & operator << (std::ostream & os, const Client & client);

#endif