/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:15:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/13 21:33:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <errno.h>
# include <fcntl.h>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdio.h>
# include <string.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include "ServerException.hpp"
# include "utils.hpp"

# define BACKLOG 20
# define POLL_TIMEOUT 2000
# define POLL_NBR_CLIENT 10
# define CLIENT_BUFFER_SIZE 256

typedef struct pollfd t_pollfd;

int create_server(int port);
void run_server(const int server, const int port, const std::string & password);

#endif