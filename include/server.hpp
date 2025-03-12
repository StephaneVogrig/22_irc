/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/11 18:55:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
#include <iostream>
# include "utils.hpp"

int create_server(int port);
void run_server(const int server, const int port, const std::string & password);

#endif