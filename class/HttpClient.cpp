/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpClient.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:41:06 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:59 by svogrig          ###   ########.fr       */
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
	int sockfd;
	char buffer[4096];

	// Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error opening socket");

	// Resolve the host
	struct addrinfo hints, *res;
	if (getaddrinfo(host.c_str(), "80", &hints, &res) != 0)
		return "";

	// Connect to the server
	if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
		throw std::runtime_error("Error connecting to server");

	// Prepare the HTTP GET request
	std::string request =   "GET " + path + " HTTP/1.1\r\n" +
							"Host: " + host + "\r\n" +
							"Connection: close\r\n\r\n";

	if (send(sockfd, request.c_str(), request.size(), 0) == -1)
		throw std::runtime_error("Error sending request");

	// Read the response
	std::string response;
	while (recv(sockfd, buffer, sizeof(buffer) - 1, 0) > 0)
		response += buffer;

	close(sockfd);
	return response;
}
