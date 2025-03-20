/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/20 19:17:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
# define PASS_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Pass : public Command
{
	public:

		Pass();
		~Pass();

		void	exec(Client * client, const std::string & arg, Server & Server);

};

#endif