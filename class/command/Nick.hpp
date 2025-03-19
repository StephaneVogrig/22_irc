/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:00 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/19 14:22:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Nick_HPP
# define Nick_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Nick : public Command
{
	public:

		Nick();
		~Nick();

		void	exec(Client * client, const std::string & arg, const Server & Server);

};

#endif