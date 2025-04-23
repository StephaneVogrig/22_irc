/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:17:42 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP
# define PING_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Server.hpp"

class Ping : public Command
{
	public:

		Ping();
		~Ping();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif