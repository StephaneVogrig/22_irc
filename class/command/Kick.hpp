/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:53 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/01 15:41:41 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
# define KICK_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Kick : public Command
{
	public:

        Kick();
		~Kick();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif