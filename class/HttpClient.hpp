/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpClient.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCLIENT_HPP
# define HTTPCLIENT_HPP

#include <iostream>
#include <sstream>
#include <cstring>
#include <netdb.h>
#include <unistd.h>

class HttpClient
{
	public:
		HttpClient();
		~HttpClient();

		std::string get(const std::string& host, const std::string& path);
};

#endif
