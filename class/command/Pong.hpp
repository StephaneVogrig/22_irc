/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/25 21:28:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONG_HPP
# define PONG_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Pong : public Command
{
	public:

		Pong();
		~Pong();

		void	exec(Client * client, const Params & params, Server & Server);

};

#endif