/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:39:10 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 19:18:48 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "Params.hpp"

# include "Mode_rpl.hpp"

class Mode : public Command
{
	public:

		Mode(void);
		~Mode(void);

		void exec(Client & client, const Params & params, Server & server);

	private:

		void exec_on_channel(Client & client, const Params & params, Server & server);

};

#endif