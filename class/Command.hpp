/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/18 16:16:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>


class Command
{
	public:

		Command(const std::string & str);
		~Command();

		void join(const std::string & params);
		void nick(const std::string & params);
		
	private:

		static std::string cmd_list[];
		static t_mbrFuncPtr func[];
};


#endif