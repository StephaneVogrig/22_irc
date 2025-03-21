/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:12:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/22 01:10:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>
# include <ctime>

# include "Client.hpp"

class Channel
{
	public:

		Channel(const std::string & name);
		Channel(const Channel & to_copy);

		~Channel(void);

		Channel & operator = (const Channel & to_assign);

		const std::string & get_name(void);
		const std::string & get_topic(void);
		const std::string & get_topic_who(void);
		const std::time_t & get_topic_setat(void);

		bool is_mode_invite_only(void);
		bool is_invited(const Client & client);

		void add_client(const Client & user, const std::string & status);
		void remove_client(const Client & user);

	private:

		const std::string					_name;
		std::string							_topic;
		std::string							_topic_who;
		std::time_t							_topic_setat;

		/*
			status :
			O : creator
			o : operator
		*/
		//   map<  nickname ,   status   >
		std::map<std::string, std::string>	_clients;

		/*
			_modes store flags :
			i : new member are only accepted if they are in _invit_list
			t : restrict the usage of the TOPIC command to channel operators
			k : user need to give a key to join the channel
			l : limit the number of user in the channel to _limit_client
		*/
		std::string							_modes;
		std::set<std::string>				_invit_list;
		std::string							_key;
		int									_limit_clients;

};

#endif