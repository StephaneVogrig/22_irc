/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:00 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 17:11:58 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDNICK_HPP
# define CMDNICK_HPP

# include <iostream>
# include "Command.hpp"

class CmdNick : public Command
{
	public:

		CmdNick();
		~CmdNick();

		void	exec(const std::string & arg);

};

#endif