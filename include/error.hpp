/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:01 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/27 23:17:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

/*405*/ void ERR_TOOMANYCHANNELS(Client & client, const std::string & channel);
void ERR_NONICKNAMEGIVEN(Client & client);
void ERR_ERRONEUSNICKNAME(Client & client, const std::string & nick);
void ERR_NICKNAMEINUSE(Client & client, const std::string & nick);
void ERR_NOTREGISTERED(Client & client, Server & server);
void ERR_ALREADYREGISTRED(Client & client);
void ERR_NEEDMOREPARAMS(Client & client, const std::string & command);
void ERR_PASSWDMISMATCH(Client & client);
/*476*/ void ERR_BADCHANMASK(Client & client, const std::string & channel);

#endif