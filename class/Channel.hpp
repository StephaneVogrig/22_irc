/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:12:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/03 12:55:24 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>
# include <ctime>
# include "log.hpp"
# include "error.hpp"

# include "Client.hpp"

class Server;

class Channel
{
	public:

		Channel(const std::string & name);
		Channel(const Channel & to_copy);

		~Channel(void);

		Channel & operator = (const Channel & to_assign);

		const std::string & get_name() const;
		const std::string & get_topic() const;
		const std::string & get_topic_who() const;
		const std::time_t & get_topic_setat() const;
		const std::string & get_modes() const;
		const std::string & get_key() const;
		const std::string & get_client_status(const Client & client);
		int 				get_limit_clients();
		int					get_nbr_client() const;

		bool is_mode_invite_only();
		bool is_mode_protected_topic();
		bool is_mode_limit_clients();
		bool is_join(const Client & client);
		bool is_invited(const Client & client);
		bool is_banned(const Client & client);
		bool is_operator(const Client & client);
		bool is_halfop(const Client & client);

		void set_topic(const Client & client, const std::string & topic);

		void invite_client(const std::string & name);

		void add_client(Client & user, const std::string & status);
		void remove_client(Client & user);

		void send_msg(const Client & client, const std::string & msg);
		void send_topic();
		void send_who(Client & sender, Server & server);
		void send_quit(Client & sender, const std::string & msg);

		static bool is_a_valid_name(const std::string & str);

	private:

		const std::string					_channel_name;
		std::string							_topic;
		std::string							_topic_who;
		std::time_t							_topic_setat;

		/*
			status :
			O : creator
			o : operator
			h : halfop
		*/
		//   map<  nickname ,   status   >
		typedef std::map<std::string, std::pair<Client *, std::string> > t_chan_clients;
		t_chan_clients	_clients;

		/*
			_modes store flags :
			i : new member are only accepted if they are in _invit_list
			t : restrict the usage of the TOPIC command to channel operators
			k : user need to give a key to join the channel
			l : limit the number of user in the channel to _limit_client
		*/
		std::string							_modes;
		std::set<std::string>				_invit_list;
		std::set<std::string>				_banned_list;
		std::string							_key;
		int									_limit_clients;

};

#endif
