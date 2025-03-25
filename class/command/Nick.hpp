/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:00 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/25 21:28:32 by svogrig          ###   ########.fr       */
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

		void	exec(Client * client, const Params & params, Server & Server);

};

#endif