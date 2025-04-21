/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:56:38 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 16:01:46 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <socket.hpp>

int create_socket(void)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw(std::runtime_error("socket failed"));
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		close(sock);
		throw(std::runtime_error("setsockoptit  failed"));
	}
	return sock;
}

void bind_socket(int sock, int port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		close(sock);
		throw(std::runtime_error("bind failed: " + std::string(strerror(errno))));
	}
}

