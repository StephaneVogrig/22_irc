/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:05 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/10 16:04:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"
#include "Server.hpp"

/*
	Error Replies
	https://www.rfc-editor.org/rfc/rfc2812#section-5.2
*/

/*
ERR_NOSUCHNICK (401)
  "<client> <nickname> :No such nick/channel"
Indicates that no client can be found for the supplied nickname. The text used in the last param of this message may vary.
*/
void ERR_401_NOSUCHNICK(Client & client, Server & server, const std::string & name)
{
	client.send_msg(":" + server.get_name() + " 401 " + client.get_nickname() + " " + name + " :No such nick/channel");
	throw Protocole_error();
}

/*
ERR_NOSUCHCHANNEL (403)
  "<client> <channel> :No such channel"
Indicates that no channel can be found for the supplied channel name. The text used in the last param of this message may vary.
*/
void ERR_403_NOSUCHCHANNEL(Client & client, const std::string & channel_name)
{
	client.send_msg("403 " + channel_name + " :No such channel");
	throw Protocole_error();
}

/*
ERR_CANNOTSENDTOCHAN (404)
  "<client> <channel> :Cannot send to channel"
Indicates that the PRIVMSG / NOTICE could not be delivered to <channel>. The text used in the last param of this message may vary.

This is generally sent in response to channel modes, such as a channel being moderated and the client not having permission to speak on the channel, or not being joined to a channel with the no external messages mode set.
*/
void ERR_404_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name)
{
	client.send_msg("404 " + channel_name + "  :Cannot send to channel");
	throw Protocole_error();
}

/*
ERR_TOOMANYCHANNELS (405)
  "<client> <channel> :You have joined too many channels"
Indicates that the JOIN command failed because the client has joined their maximum number of channels. The text used in the last param of this message may vary.
*/
void ERR_405_TOOMANYCHANNELS(Client & client, const std::string & channel_name)
{
	client.send_msg("405 " + channel_name + " :You have joined too many channels");
	throw Protocole_error();
}

/*
ERR_NOTEXTTOSEND (412)
  "<client> :No text to send"
Returned by the PRIVMSG command to indicate the message wasn’t delivered because there was no text to send.
*/
void ERR_412_NOTEXTTOSEND(Client & client)
{
	client.send_msg("412 " + client.get_nickname() + " :No text to send");
	throw Protocole_error();
}

/*
ERR_UNKNOWNCOMMAND (421)
  "<client> <command> :Unknown command"
Sent to a registered client to indicate that the command they sent isn’t known by the server. The text used in the last param of this message may vary.
*/
void ERR_421_UNKNOWNCOMMAND(Client & client, const std::string & command)
{
	client.send_msg("421 " + client.get_nickname() + " " + command + " :Unknown command");
	throw Protocole_error();
}

/*
ERR_NONICKNAMEGIVEN (431)
  "<client> :No nickname given"
Returned when a nickname parameter is expected for a command but isn’t given.
*/
void ERR_431_NONICKNAMEGIVEN(Client & client)
{
	client.send_msg("431 :No nickname given");
	throw Protocole_error();
}

/*
ERR_ERRONEUSNICKNAME (432)
  "<client> <nick> :Erroneus nickname"
Returned when a NICK command cannot be successfully completed as the desired nickname contains characters that are disallowed by the server. See the NICK command for more information on characters which are allowed in various IRC servers. The text used in the last param of this message may vary.
*/
void ERR_432_ERRONEUSNICKNAME(Client & client, const std::string & nick)
{
	client.send_msg("432 " + nick + " :Erroneous nickname");
	throw Protocole_error();
}

/*
ERR_NICKNAMEINUSE (433)
  "<client> <nick> :Nickname is already in use"
Returned when a NICK command cannot be successfully completed as the desired nickname is already in use on the network. The text used in the last param of this message may vary.
*/
void ERR_433_NICKNAMEINUSE(Client & client, const std::string & nick)
{
	client.send_msg(": 433 * " + nick + " :Nickname is already in use");
	throw Protocole_error();
}

/*
ERR_USERNOTINCHANNEL (441)
  "<client> <nick> <channel> :They aren't on that channel"
Returned when a client tries to perform a channel+nick affecting command, when the nick isn’t joined to the channel (for example, MODE #channel +o nick).
*/
void ERR_441_USERNOTINCHANNEL(Client & client, const std::string & name, const Channel & channel)
{
	client.send_msg("441 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :They aren't on that channel");
	throw Protocole_error();
}

/*
ERR_NOTONCHANNEL (442)
  "<client> <channel> :You're not on that channel"
Returned when a client tries to perform a channel-affecting command on a channel which the client isn’t a part of.
*/
void ERR_442_NOTONCHANNEL(Client & client, const Channel & channel)
{
	client.send_msg("442 " + channel.get_name() + " :You're not on that channel");
	throw Protocole_error();
}

/*
ERR_USERONCHANNEL (443)
  "<client> <nick> <channel> :is already on channel"
Returned when a client tries to invite <nick> to a channel they’re already joined to.
*/
void ERR_443_USERONCHANNEL(Client & client, const std::string & name, const Channel & channel)
{
	client.send_msg("443 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :is already on channell");
	throw Protocole_error();
}

/*
ERR_NOTREGISTERED (451)
  "<client> :You have not registered"
Returned when a client command cannot be parsed as they are not yet registered. Servers offer only a limited subset of commands until clients are properly registered to the server. The text used in the last param of this message may vary.
*/
void ERR_451_NOTREGISTERED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 451 :You have not registered");
	throw Protocole_error();
}

/*
ERR_NEEDMOREPARAMS (461)
  "<client> <command> :Not enough parameters"
Returned when a client command cannot be parsed because not enough parameters were supplied. The text used in the last param of this message may vary.
*/
void ERR_461_NEEDMOREPARAMS(Client & client, const std::string & command)
{
	client.send_msg("461 " + command + " :Not enough parameters");
	throw Protocole_error();
}

/*
ERR_ALREADYREGISTERED (462)
  "<client> :You may not reregister"
Returned when a client tries to change a detail that can only be set during registration (such as resending the PASS or USER after registration). The text used in the last param of this message varies.
*/
void ERR_462_ALREADYREGISTRED(Client & client)
{
	client.send_msg("462 :Unauthorized command (already registered)");
	throw Protocole_error();
}

/*
ERR_PASSWDMISMATCH (464)
  "<client> :Password incorrect"
Returned to indicate that the connection could not be registered as the password was either incorrect or not supplied. The text used in the last param of this message may vary.
*/
void ERR_464_PASSWDMISMATCH(Client & client)
{
	client.send_msg("464 :Password incorrect");
	throw Protocole_error();
}

/*
467    ERR_KEYSET
		"<channel> :Channel key already set"
*/
void ERR_467_KEYSET(Client & client, const Channel & channel)
{
	client.send_msg("467 " + channel.get_name() + " :Channel key already set");
	throw Protocole_error();
}

/*
ERR_CHANNELISFULL (471)
  "<client> <channel> :Cannot join channel (+l)"
Returned to indicate that a JOIN command failed because the client limit mode has been set and the maximum number of users are already joined to the channel. The text used in the last param of this message may vary.
*/
void ERR_471_CHANNELISFULL(Client & client, const Channel & channel)
{
	client.send_msg("471 " + channel.get_name() + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*
ERR_UNKNOWNMODE (472)
  "<client> <modechar> :is unknown mode char to me"
Indicates that a mode character used by a client is not recognized by the server. The text used in the last param of this message may vary.
*/
void ERR_472_UNKNOWNMODE(Client & client, char modechar)
{
	client.send_msg("472 " + client.get_nickname() + modechar + " :is unknown mode char to me");
	throw Protocole_error();
}

/*
ERR_INVITEONLYCHAN (473)
  "<client> <channel> :Cannot join channel (+i)"
Returned to indicate that a JOIN command failed because the channel is set to [invite-only] mode and the client has not been invited to the channel or had an invite exception set for them. The text used in the last param of this message may vary.
*/
void ERR_473_INVITEONLYCHAN(Client & client, const std::string & channel)
{
	client.send_msg("473 " + channel + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*
ERR_BANNEDFROMCHAN (474)
  "<client> <channel> :Cannot join channel (+b)"
Returned to indicate that a JOIN command failed because the client has been banned from the channel and has not had a ban exception set for them. The text used in the last param of this message may vary.
*/
void ERR_474_BANNEDFROMCHAN(Client & client, const std::string & channel)
{
	client.send_msg("473 " + channel + " :Cannot join channel (+b)");
	throw Protocole_error();
}

/*
ERR_BADCHANNELKEY (475)
  "<client> <channel> :Cannot join channel (+k)"
Returned to indicate that a JOIN command failed because the channel requires a key and the key was either incorrect or not supplied. The text used in the last param of this message may vary.

Not to be confused with ERR_INVALIDKEY, which may be returned when setting a key.
*/
void ERR_475_BADCHANNELKEY(Client & client, const std::string & channel)
{
	client.send_msg("475 " + channel + " :Cannot join channel (+k)");
	throw Protocole_error();
}

/*
ERR_BADCHANMASK (476)
  "<channel> :Bad Channel Mask"
Indicates the supplied channel name is not a valid.

This is similar to, but stronger than, ERR_NOSUCHCHANNEL (403), which indicates that the channel does not exist, but that it may be a valid name.

The text used in the last param of this message may vary.
*/
void ERR_476_BADCHANMASK(Client & client, const std::string & channel, Server & server)
{
	client.send_msg(":" + server.get_name() + " 476 " + channel + " :Bad Channel Mask");
	throw Protocole_error();
}

/*
ERR_CHANOPRIVSNEEDED (482)
  "<client> <channel> :You're not channel operator"
Indicates that a command failed because the client does not have the appropriate channel privileges. This numeric can apply for different prefixes such as halfop, operator, etc. The text used in the last param of this message may vary.
*/
void ERR_482_CHANOPRIVSNEEDED(Client & client, const Channel & channel)
{
	client.send_msg("482 " + channel.get_name() + " :You're not channel operator");
	throw Protocole_error();
}

/*
ERR_INVALIDMODEPARAM (696)
"<client> <target chan/user> <mode char> <parameter> :<description>"
Indicates that there was a problem with a mode parameter. Replaces various implementation-specific mode-specific numerics.
*/
void ERR_696_INVALIDMODEPARAM(Client & client, const std::string & target, char mode, const std::string & parameter, const std::string & description)
{
	client.send_msg("696 " + client.get_nickname() + " " + target + " " + mode + " " + parameter + " :" + description);
	throw Protocole_error();
}
