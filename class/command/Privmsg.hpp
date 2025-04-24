/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:08 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:17:37 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Server.hpp"

class Privmsg : public Command
{
	public:

		Privmsg();
		~Privmsg();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif