/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 20:37:51 by gcannaud         ###   ########.fr       */
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
		const std::string get_nickname(void) const;
		const std::string get_username(void) const;
		bool is_registed() const;
		void set_nickname(std::string name);
		void set_username(std::string name);
		void registed();

		void append_to_buffer(const std::string & str);
		void clear_msg_buffer(void);

	private :

		int			_fd;
		std::string _msg_buffer;

		std::string _userName;
		std::string _realName;
		std::string _nickName;

		bool		_registed;

};

std::ostream & operator << (std::ostream & os, const Client & client);

#endif