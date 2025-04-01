/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/01 19:49:06 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CPP
# define CLIENT_CPP

# include <iostream>
# include <sys/socket.h>
# include <vector>
# include <algorithm>

class Channel;

class Client
{
	public :

		Client(int fd);
		~Client();

		const std::string & get_msg_buffer() const;
		int get_fd();
		const std::string get_nickname() const;
		const std::string get_username() const;
		const std::string get_realname() const;
		bool is_registed() const;
		bool is_hasPass() const;
		bool is_kicked() const;
		void set_hasPass(bool pass);
		void set_kicked(bool kick);
		void set_nickname(std::string name);
		void set_username(std::string name);
		void set_realname(std::string name);

		void append_to_buffer(const std::string & str);
		void clear_msg_buffer();

		void send_msg(const std::string & msg) const;

		void		add_channel_subscripted(Channel & channel);
		void		remove_channel_subscripted(Channel & channel);
		Channel *	get_last_channel_subscripted();
		Channel *	get_last_channel_subscripted();
		int			nbr_channels_subscripted();
		void		quit_all_channels();

	private :

		int			_fd;
		std::string _msg_buffer;

		std::string _nickName;
		std::string _userName;
		std::string _realName;

		bool _hasPass;

		bool _kicked;

		std::string _hostname;
		std::string _hostadress;

		typedef std::vector<Channel *> t_channels;
		t_channels _channels_subscripted;

};

std::ostream & operator << (std::ostream & os, const Client & client);

#endif