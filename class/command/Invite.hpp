/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:38:36 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/01 15:41:32 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
# define INVITE_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Invite : public Command
{
	public:
		Invite(void);
		~Invite(void);

		void exec(Client & client, const Params & params, Server & server);

};

#endif