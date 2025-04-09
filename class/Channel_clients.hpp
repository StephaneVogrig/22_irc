/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_clients.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:44:26 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/09 21:57:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLIENTS_HPP
# define CHANNEL_CLIENTS_HPP

# include <string>
# include "Client.hpp"

class Channel_clients
{
	public:
		Channel_clients();
		Channel_clients(const Channel_clients & to_copy);

		~Channel_clients();

		Channel_clients & operator = (const Channel_clients & to_assign);

		int 				get_nbr() const;
		const std::string &	get_status(const Client & client);
		Client *			get_client_ptr_by_nickname(const std::string & nickname);
		
		void add(const Client & client);
		void remove(const Client & client);
		void set_status(const Client & client, std::string);
		void unset_status(const Client & client, std::string);

	private:

	

};

#endif