/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:00 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:18:18 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Nick_HPP
# define Nick_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Server.hpp"

class Nick : public Command
{
	public:

		Nick();
		~Nick();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif