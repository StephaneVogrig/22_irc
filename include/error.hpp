/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:01 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 13:32:33 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include "Client.hpp"
# include "Channel.hpp"

void ERR_NICKNAMEINUSE(Client & client, const std::string & nick);
void ERR_NOTREGISTERED(Client & client);
void ERR_ALREADYREGISTRED(Client & client);
void ERR_NEEDMOREPARAMS(Client & client, const std::string & command);
void ERR_PASSWDMISMATCH(Client & client);
#endif