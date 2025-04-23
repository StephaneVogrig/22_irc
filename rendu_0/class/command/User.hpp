/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:08 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/26 12:04:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef User_HPP
# define User_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class User : public Command
{
	public:

		User();
		~User();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif