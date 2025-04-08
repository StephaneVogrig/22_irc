/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:02:37 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 17:47:33 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
# define LOG_HPP

# include <string>
#include <ostream>
#include <iostream>
#include <iomanip>
# include "utils.hpp"

void log_(const std::string & msg);
void log_msg(int fd, const std::string & action, const std::string & msg);
void log_server(int fd, const std::string & msg);

#endif
