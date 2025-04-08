/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:39:10 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 04:06:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# include "Command.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Elements.hpp"
# include "reply.hpp"
# include <queue>

class Mode : public Command
{
	public:

		Mode(void);
		~Mode(void);

		void exec(Client & client, const Params & params, Server & server);

	private:

		void exec_on_channel(Client & client, const Params & params, Server & server);
		void exec_on_user(Client & client, const Params & params, Server & server);

};

#endif