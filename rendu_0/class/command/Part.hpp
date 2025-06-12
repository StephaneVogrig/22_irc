/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:31 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:23:30 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
# define PART_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Server.hpp"

# include "Elements.hpp"

class Part : public Command
{
	public:

        Part();
		~Part();

		void	exec(Client & client, const Params & params, Server & Server);

};

#endif
