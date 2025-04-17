/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpClient.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/18 00:03:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpClient.hpp"

HttpClient::HttpClient()
{
}

HttpClient::~HttpClient()
{
}

std::string HttpClient::get(const std::string& host, const std::string& path)
{
	// Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error opening socket");

	// Resolve the host
	struct addrinfo		hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	struct addrinfo *	result;

	if (getaddrinfo(host.c_str(), "80", &hints, &result) != 0)
		return "";

	// Connect to the server
	if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0)
		throw std::runtime_error("Error connecting to server");

	freeaddrinfo(result);

	// Prepare the HTTP GET request
	std::string request =   "GET " + path + " HTTP/1.1\r\n" +
							"Host: " + host + "\r\n" +
							"Connection: close\r\n\r\n";

	if (send(sockfd, request.c_str(), request.size(), 0) == -1)
		throw std::runtime_error("Error sending request");

	// Read the response
	std::string response;
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	while (recv(sockfd, buffer, sizeof(buffer) - 1, 0) > 0)
		response += buffer;

	close(sockfd);

	return response;
}
