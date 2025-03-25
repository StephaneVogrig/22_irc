/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/25 21:37:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include "Params.hpp"
# include "utils.hpp"

class Server;
class Client;

class Command
{
	public:

		Command(const std::string & name = "default");
		Command(const Command &to_cpy);
		virtual ~Command();
		Command & operator=(const Command & to_assign);

		virtual void	exec(Client * client, const Params & params, Server & Server);

	protected:
		
		const std::string _name;

};

#endif