/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:08 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/20 19:15:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Quit : public Command
{
	public:

		Quit();
		~Quit();

		void	exec(Client * client, const std::string & arg, Server & Server);

};

#endif