/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/03/18 17:11:33 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdUser.hpp"

CmdUser::CmdUser()
{
}

CmdUser::~CmdUser()
{
}

void CmdUser::exec(const std::string & arg)
{
	std::cout << PURPLE "this command is USER" RESET << std::endl;
	std::cout << PURPLE "arg = " RESET << arg  << std::endl;

}
