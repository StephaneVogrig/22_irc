/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:05 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 20:43:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"
#include "Server.hpp"

void ERR_401_NOSUCHNICK(Client & client, Server & server, const std::string & name)
{
	client.send_msg(":" + server.get_name() + " 401 " + client.get_nickname() + " " + name + " :No such nickname");
	throw Protocole_error();
}

void ERR_403_NOSUCHCHANNEL(Client & client, const std::string & channel_name, Server & server)
{
	client.send_msg(":" + server.get_name() + " 403 " + channel_name + " :No such channel");
	throw Protocole_error();
}

void ERR_404_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name, Server & server)
{
	client.send_msg(":" + server.get_name() + " 404 " + channel_name + "  :Cannot send to channel");
	throw Protocole_error();
}

void ERR_405_TOOMANYCHANNELS(Client & client, const std::string & channel_name, Server & server)
{
	client.send_msg(":" + server.get_name() + " 405 " + channel_name + " :You have joined too many channels");
	throw Protocole_error();
}

void ERR_412_NOTEXTTOSEND(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 412 " + client.get_nickname() + " :No text to send");
	throw Protocole_error();
}

void ERR_421_UNKNOWNCOMMAND(Client & client, const std::string & command, Server & server)
{
	client.send_msg(":" + server.get_name() + " 421 " + client.get_nickname() + " " + command + " :Unknown command");
	throw Protocole_error();
}

void ERR_431_NONICKNAMEGIVEN(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 431 :No nickname given");
	throw Protocole_error();
}

void ERR_432_ERRONEUSNICKNAME(Client & client, const std::string & nick, Server & server)
{
	client.send_msg(":" + server.get_name() + " 432 " + nick + " :Erroneous nickname");
	throw Protocole_error();
}

void ERR_433_NICKNAMEINUSE(Client & client, const std::string & nick, Server & server)
{
	client.send_msg(":" + server.get_name() + " 433 * " + nick + " :Nickname is already in use");
	throw Protocole_error();
}

void ERR_441_USERNOTINCHANNEL(Client & client, const std::string & name, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 441 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :They aren't on that channel");
	throw Protocole_error();
}

void ERR_442_NOTONCHANNEL(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 442 " + channel.get_name() + " :You're not on that channel");
	throw Protocole_error();
}

void ERR_443_USERONCHANNEL(Client & client, const std::string & name, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 443 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :is already on channell");
	throw Protocole_error();
}

void ERR_451_NOTREGISTERED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 451 :You have not registered");
	throw Protocole_error();
}

void ERR_461_NEEDMOREPARAMS(Client & client, const std::string & command, Server & server)
{
	client.send_msg(":" + server.get_name() + " 461 " + client .get_nickname() + " " + command + " :Not enough parameters");
	throw Protocole_error();
}

void ERR_462_ALREADYREGISTRED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 462 " + client.get_nickname() + " :Already registered");
	throw Protocole_error();
}

void ERR_464_PASSWDMISMATCH(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 464 :Password incorrect");
	throw Protocole_error();
}

void ERR_467_KEYSET(Client & client, const Channel & channel, Server & server, char c)
{
	client.send_msg(":" + server.get_name() + " 467 " + client .get_nickname() + " " + channel.get_name() + " :Channel key " + c + " already set");
	throw Protocole_error();
}

void ERR_471_CHANNELISFULL(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 471 " + channel.get_name() + " :Cannot join channel (+l)");
	throw Protocole_error();
}

void ERR_472_UNKNOWNMODE(Client & client, char modechar, Server & server)
{
	client.send_msg(":" + server.get_name() + " 472 " + client.get_nickname() + " " + modechar + " :is unknown mode char to me");
	throw Protocole_error();
}

void ERR_473_INVITEONLYCHAN(Client & client, const std::string & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 473 " + client.get_nickname() + " " + channel + " :Cannot join channel (+i)");
	throw Protocole_error();
}

void ERR_474_BANNEDFROMCHAN(Client & client, const std::string & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 473 " + channel + " :Cannot join channel (+b)");
	throw Protocole_error();
}

void ERR_475_BADCHANNELKEY(Client & client, const std::string & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 475 " + channel + " :Cannot join channel (+k)");
	throw Protocole_error();
}

void ERR_476_BADCHANMASK(Client & client, const std::string & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 476 " + channel + " :Bad Channel Mask");
	throw Protocole_error();
}

void ERR_482_CHANOPRIVSNEEDED(Client & client, const Channel & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 482 " + client.get_nickname() + " " + channel.get_name() + " :You're not channel operator");
	throw Protocole_error();
}

void ERR_696_INVALIDMODEPARAM(Client & client, const std::string & target, char mode, const std::string & parameter, const std::string & description, Server & server)
{
	client.send_msg(":" + server.get_name() + " 696 " + client.get_nickname() + " " + target + " " + mode + " " + parameter + " :" + description);
	throw Protocole_error();
}
