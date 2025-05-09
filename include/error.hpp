/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:01 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/10 17:30:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include "Client.hpp"
# include "Channel.hpp"

class Server;

void ERR_401_NOSUCHNICK(Client & client, Server & server, const std::string & name);
void ERR_403_NOSUCHCHANNEL(Client & client, const std::string & channel_name, Server & server);
void ERR_404_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name, Server & server);
void ERR_405_TOOMANYCHANNELS(Client & client, const std::string & channel_name, Server & server);
void ERR_412_NOTEXTTOSEND(Client & client, Server & server);
void ERR_421_UNKNOWNCOMMAND(Client & client, const std::string & command, Server & server);
void ERR_431_NONICKNAMEGIVEN(Client & client, Server & server);
void ERR_432_ERRONEUSNICKNAME(Client & client, const std::string & nick, Server & server);
void ERR_433_NICKNAMEINUSE(Client & client, const std::string & nick, Server & server);
void ERR_441_USERNOTINCHANNEL(Client & client, const std::string & name, const Channel & channel, Server & server);
void ERR_442_NOTONCHANNEL(Client & client, const Channel & channel, Server & server);
void ERR_443_USERONCHANNEL(Client & client, const std::string & name, const Channel & channel, Server & server);
void ERR_451_NOTREGISTERED(Client & client, Server & server);
void ERR_461_NEEDMOREPARAMS(Client & client, const std::string & command, Server & server);
void ERR_462_ALREADYREGISTRED(Client & client, Server & server);
void ERR_464_PASSWDMISMATCH(Client & client, Server & server);
void ERR_467_KEYSET(Client & client, const Channel & channel, Server & server, char c);
void ERR_471_CHANNELISFULL(Client & client, const Channel & channel, Server & server);
void ERR_472_UNKNOWNMODE(Client & client, char modechar, Server & server);
void ERR_473_INVITEONLYCHAN(Client & client, const std::string & channel, Server & server);
void ERR_474_BANNEDFROMCHAN(Client & client, const std::string & channel, Server & server);
void ERR_475_BADCHANNELKEY(Client & client, const std::string & channel, Server & server);
void ERR_476_BADCHANMASK(Client & client, const std::string & channel, Server & server);
void ERR_482_CHANOPRIVSNEEDED(Client & client, const Channel & channel, Server & server);
void ERR_696_INVALIDMODEPARAM(Client & client, const std::string & target, char mode, const std::string & parameter, const std::string & description, Server & server);

#endif