/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:57 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/30 21:38:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "Command.hpp"

# include "Client.hpp"
# include "Params.hpp"
# include "Server.hpp"

# include "reply.hpp"
# include "error.hpp"

class Topic : public Command
{
	public:
		Topic(void);
		~Topic(void);

		void exec(Client & client, const Params & params, Server & server);
};

#endif
