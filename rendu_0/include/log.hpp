/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:02:37 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 18:21:26 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
# define LOG_HPP

# include <string>
# include <ostream>
# include <iostream>
# include <iomanip>
# include "utils.hpp"

void log_(const std::string & msg);
void log_msg(int fd, const std::string & action, const std::string & msg);
void log_server(int fd, const std::string & msg);

#endif
