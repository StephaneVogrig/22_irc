/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:12:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/12 22:28:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>
# include <climits>

# include "log.hpp"
# include "error.hpp"
# include "Client.hpp"
# include "log.hpp"

class Server;

class Channel
{
	public:

		Channel(const std::string & name, const std::string & key = "");
		Channel(const Channel & to_copy);

		~Channel(void);

		Channel & operator = (const Channel & to_assign);

		const std::string & get_name() const;
		const std::time_t & get_creation_time() const;
		const std::string & get_topic() const;
		const std::string & get_topic_who() const;
		const std::time_t & get_topic_setat() const;
		const std::string & get_modes() const;
		const std::string & get_key() const;
		const std::string & get_client_status(const Client & client) const;
		int 				get_limit_nbr_client() const;
		int					get_nbr_client() const;
		std::string			get_clients() const;

		bool is_mode_invite_only() const;
		bool is_mode_protected_topic() const;
		bool is_mode_key_needed() const;
		bool is_mode_limit_nbr_client() const;
		bool is_join(const Client & client) const;
		bool is_invited(const Client & client) const;
		bool is_founder(const Client & client) const;
		bool is_operator(const Client & client) const;
		bool is_halfop(const Client & client) const;
		bool has_an_operator() const;

		void set_topic(Client & client, const std::string & topic, Server & server);
		void set_mode(char c);
		void unset_mode(char c);
		void set_key(const std::string & keystring);
		void set_client_status(const Client & client, char status);
		void unset_client_status(const Client & client, char status);
		void set_limit(int nbr);
		void set_random_operator(Server & server);

		void invite_client(const Client & client);
		void remove_from_invited(const Client & client);

		void add_client(Client & user, const std::string & status);
		void remove_client(Client & user);

		void send_to_all(const std::string & sender, const std::string & msg);
		void send_to_others(const Client & sender, const std::string & cmd, const std::string & msg);
;
		void send_who(Client & sender, Server & server);
		void send_quit(Client & sender, const std::string & msg);

		void log(const std::string & action);
		void log(const std::string & action, const std::string & who);

		static bool is_a_valid_name(const std::string & str);

	private:

		const std::string					_channel_name;
		const std::time_t					_creation_time;
		std::string							_topic;
		std::string							_topic_who;
		std::time_t							_topic_setat;

		/*
					status	prefix
			founder		q		~
			operator	o		@
			halfop		h		%
		*/
		//   map < fd, < ptr, status > >
		typedef std::map<int, std::pair<Client *, std::string> > t_chan_clients;
		t_chan_clients _chan_clients;

		/*
			_modes store flags :
			i : new member are only accepted if they are in _invited
			t : restrict the usage of the TOPIC command to channel operators
			k : user need to give a key to join the channel
			l : limit the number of user in the channel to _limit_client
		*/
		std::string	_modes;

		typedef std::set<int> t_invited;
		t_invited	_invited;

		std::string	_key;
		int			_limit_nbr_client;

};

#endif
