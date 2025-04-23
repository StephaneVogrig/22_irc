/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:58:02 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 16:02:39 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <cstring>
# include <cerrno>

# include <stdexcept>

int		create_socket(void);
void	bind_socket(int sock, int port);

#endif
