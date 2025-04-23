/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:33:32 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 19:53:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

# include "Command.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Elements.hpp"
# include "reply.hpp"

class Join : public Command
{
	public:
		Join(void);
		~Join(void);

		void exec(Client & client, const Params & params, Server & server);
		void exec_solo(Client & client, const std::string & channel_name, const std::string & key, Server & server);
};

#endif