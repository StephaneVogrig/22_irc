/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:53 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:18:58 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
# define KICK_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "Params.hpp"

class Kick : public Command
{
	public:

        Kick();
		~Kick();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif