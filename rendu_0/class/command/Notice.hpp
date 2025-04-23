/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:08 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:04:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
# define NOTICE_HPP

# include <iostream>
# include "Command.hpp"
# include "reply.hpp"

class Server;
class Client;

class Notice : public Command
{
	public:

	Notice();
		~Notice();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif