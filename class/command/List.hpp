/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:36:54 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:18:53 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "Params.hpp"

class List : public Command
{

	public:

		List();
		~List();

		void exec(Client & client, const Params & params, Server & server);

};

#endif
