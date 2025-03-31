/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:31 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/31 19:14:02 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
# define PART_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class Part : public Command
{
	public:

        Part();
		~Part();

		void	exec(Client & client, const Params & params, Server & Server);

};


#endif