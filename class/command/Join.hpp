/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:33:32 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/20 19:16:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

# include "Command.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Join : public Command
{
	public:
		Join(void);
		~Join(void);

		void exec(Client * client, const std::string & param, Server & server);
};

#endif