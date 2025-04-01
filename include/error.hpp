/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:01 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/01 14:38:19 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

/*401*/ void ERR_NOSUCHNICK(Client & client, Server & server, const std::string & name);
/*403*/ void ERR_NOSUCHCHANNEL(Client & client, const std::string & channel_name);
/*404*/ void ERR_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name);
/*405*/ void ERR_TOOMANYCHANNELS(Client & client, const std::string & channel_name);
/*421*/ void ERR_UNKNOWNCOMMAND(Client & client, const std::string & command);
/*431*/ void ERR_NONICKNAMEGIVEN(Client & client);
/*432*/ void ERR_ERRONEUSNICKNAME(Client & client, const std::string & nick);
/*433*/ void ERR_NICKNAMEINUSE(Client & client, const std::string & nick);
/*441*/ void ERR_USERNOTINCHANNEL(Client & client, const std::string & name, const Channel & channel);
/*442*/ void ERR_NOTONCHANNEL(Client & client, const Channel & channel);
/*451*/ void ERR_NOTREGISTERED(Client & client, Server & server); // retirer serveur ?
/*461*/ void ERR_NEEDMOREPARAMS(Client & client, const std::string & command);
/*462*/ void ERR_ALREADYREGISTRED(Client & client);
/*464*/ void ERR_PASSWDMISMATCH(Client & client);
/*471*/ void ERR_CHANNELISFULL(const Client & client, const Channel & channel);
/*473*/ void ERR_INVITEONLYCHAN(Client & client, const std::string & channel);
/*474*/ void ERR_BANNEDFROMCHAN(Client & client, const std::string & channel);
/*475*/ void ERR_BADCHANNELKEY(Client & client, const std::string & channel);
/*476*/ void ERR_BADCHANMASK(Client & client, const std::string & channel);
/*482*/ void ERR_CHANOPRIVSNEEDED(const Client & client, const Channel & channel);

#endif