/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 18:24:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void run_server(const int port, const std::string & password)
{
	std::cout	<< BLUE "ask run server on port " RESET << port
				<< BLUE " with password " RESET << password << std::endl;
}