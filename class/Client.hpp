/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/21 05:12:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CPP
# define CLIENT_CPP

# include <iostream>
# include <sys/socket.h>

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
		bool is_hasPass() const;
		void set_hasPass(bool pass);
		void set_nickname(std::string name);
		void set_username(std::string name);

		void append_to_buffer(const std::string & str);
		void clear_msg_buffer(void);

		void send_msg(const std::string & msg);

	private :

		int			_fd;
		std::string _msg_buffer;

		std::string _nickName;
		std::string _userName;
		std::string _realName;

		bool _hasPass;

		std::string _hostname;
		std::string _hostadress;

};

std::ostream & operator << (std::ostream & os, const Client & client);

#endif