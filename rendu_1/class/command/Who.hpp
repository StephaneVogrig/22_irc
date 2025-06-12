/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:02:16 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:16:30 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Who_HPP
# define Who_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Server.hpp"

class Who : public Command
{
	public:

        Who();
		~Who();

		void	exec(Client & client, const Params & params, Server & Server);

        private:

		void exec_on_channel(Client & client, const Params & params, Server & server);
		void exec_on_user(Client & client, const Params & params, Server & server);

};

#endif