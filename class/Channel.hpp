/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:12:34 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/19 14:17:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>

# include "Client.hpp"

class Channel
{
	public:

		Channel(const std::string & name);
		Channel(const Channel & to_copy);

		~Channel(void);

		Channel & operator = (const Channel & to_assign);

		const std::string & get_name(void);

		void add_client(const Client & user);
		void remove_client(const Client & user);

	private:

		const std::string					_name;
		std::string							_topic;

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