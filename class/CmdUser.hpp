/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:08 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 20:07:07 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDUSER_HPP
# define CMDUSER_HPP

# include <iostream>
# include "Command.hpp"

class Server;
class Client;

class CmdUser : public Command
{
	public:

		CmdUser();
		~CmdUser();

		void	exec(Client * client, const std::string & arg, const Server & Server);

};

#endif