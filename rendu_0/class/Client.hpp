/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:11:15 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 18:24:25 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CPP
# define CLIENT_CPP

# include <iostream>
# include <sys/socket.h>
# include <vector>
# include <algorithm>

class Channel;
class Server;

class Client
{
	public :

		Client(int fd, struct sockaddr_in addr);
		~Client();

		const std::string & get_msg_buffer() const;
		int get_fd() const;
		const std::string get_nickname() const;
		const std::string get_username() const;
		const std::string get_realname() const;
		const std::string get_hostname() const;
		const std::string get_hostadress() const;

		bool is_registed() const;
		bool is_hasPass() const;
		void set_hasPass(bool pass);
		void set_nickname(std::string name);
		void set_username(std::string name);
		void set_realname(std::string name);

		void append_to_buffer(const std::string & str);
		void clear_msg_buffer();

		void send_msg(const std::string & msg);

		void		add_channel_subscripted(Channel & channel);
		void		remove_channel_subscripted(Channel & channel);
		Channel *	get_last_channel_subscripted();
		int			nbr_channels_subscripted();
		void		send_on_all_channels(const std::string & msg);
		void		part_all_channels(Server & server);
		void 		quit_all_channels(Server & server, const std::string & msg);

		static bool	is_a_valid_nickname(const std::string & nickname);

	private :

		int			_fd;
		std::string _msg_buffer;

		std::string _nickName;
		std::string _userName;
		std::string _realName;

		std::string		_hostname;
		std::string		_hostadress;

		typedef std::vector<Channel *> t_channels;
		t_channels	_channels_subscripted;

		bool _connection_ko;
		bool _hasPass;

};

std::ostream & operator << (std::ostream & os, const Client & client);

#endif