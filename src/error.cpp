/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:05 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/07 19:11:43 by svogrig          ###   ########.fr       */
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
void ERR_NOSUCHNICK(Client & client, Server & server, const std::string & name)
{
	client.send_msg(":" + server.get_name() + " 401 " + client.get_nickname() + " " + name + " :No such nick/channel");
	throw Protocole_error();
}

/*
402    ERR_NOSUCHSERVER
		"<server name> :No such server"

	- Used to indicate the server name given currently
	does not exist.
*/

/*
ERR_NOSUCHCHANNEL (403)
  "<client> <channel> :No such channel"
Indicates that no channel can be found for the supplied channel name. The text used in the last param of this message may vary.
*/
void ERR_NOSUCHCHANNEL(Client & client, const std::string & channel_name)
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
void ERR_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name)
{
	client.send_msg("404 " + channel_name + "  :Cannot send to channel");
	throw Protocole_error();
}

/*
ERR_TOOMANYCHANNELS (405)
  "<client> <channel> :You have joined too many channels"
Indicates that the JOIN command failed because the client has joined their maximum number of channels. The text used in the last param of this message may vary.
*/
void ERR_TOOMANYCHANNELS(Client & client, const std::string & channel_name)
{
	client.send_msg("405 " + channel_name + " :You have joined too many channels");
	throw Protocole_error();
}

/*
406    ERR_WASNOSUCHNICK
		"<nickname> :There was no such nickname"

	- Returned by WHOWAS to indicate there is no history
	information for that nickname.

407    ERR_TOOMANYTARGETS
		"<target> :<error code> recipients. <abort message>"

	- Returned to a client which is attempting to send a
	PRIVMSG/NOTICE using the user@host destination format
	and for a user@host which has several occurrences.

	- Returned to a client which trying to send a
	PRIVMSG/NOTICE to too many recipients.

	- Returned to a client which is attempting to JOIN a safe
	channel using the shortname when there are more than one
	such channel.

408    ERR_NOSUCHSERVICE
		"<service name> :No such service"

	- Returned to a client which is attempting to send a SQUERY
	to a service which does not exist.

409    ERR_NOORIGIN
		":No origin specified"

	- PING or PONG message missing the originator parameter.

411    ERR_NORECIPIENT
		":No recipient given (<command>)"
*/

/*
ERR_NOTEXTTOSEND (412)
  "<client> :No text to send"
Returned by the PRIVMSG command to indicate the message wasn’t delivered because there was no text to send.
*/
void ERR_NOTEXTTOSEND(Client & client)
{
	client.send_msg("412 " + client.get_nickname() + " :No text to send");
	throw Protocole_error();
}

/*
413    ERR_NOTOPLEVEL
		"<mask> :No toplevel domain specified"
414    ERR_WILDTOPLEVEL
		"<mask> :Wildcard in toplevel domain"
415    ERR_BADMASK
		"<mask> :Bad Server/host mask"

	- 412 - 415 are returned by PRIVMSG to indicate that
	the message wasn't delivered for some reason.
	ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
	are returned when an invalid use of
	"PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/

/*
ERR_UNKNOWNCOMMAND (421)
  "<client> <command> :Unknown command"
Sent to a registered client to indicate that the command they sent isn’t known by the server. The text used in the last param of this message may vary.
*/
void ERR_UNKNOWNCOMMAND(Client & client, const std::string & command)
{
	client.send_msg("421 " + client.get_nickname() + " " + command + " :Unknown command");
	throw Protocole_error();
}

/*
422    ERR_NOMOTD
		":MOTD File is missing"

	- Server's MOTD file could not be opened by the server.

423    ERR_NOADMININFO
		"<server> :No administrative info available"

	- Returned by a server in response to an ADMIN message
	when there is an error in finding the appropriate
	information.

424    ERR_FILEERROR
		":File error doing <file op> on <file>"

	- Generic error message used to report a failed file
	operation during the processing of a message.
*/

/*
ERR_NONICKNAMEGIVEN (431)
  "<client> :No nickname given"
Returned when a nickname parameter is expected for a command but isn’t given.
*/
void ERR_NONICKNAMEGIVEN(Client & client)
{
	client.send_msg("431 :No nickname given");
	throw Protocole_error();
}

/*
ERR_ERRONEUSNICKNAME (432)
  "<client> <nick> :Erroneus nickname"
Returned when a NICK command cannot be successfully completed as the desired nickname contains characters that are disallowed by the server. See the NICK command for more information on characters which are allowed in various IRC servers. The text used in the last param of this message may vary.
*/
void ERR_ERRONEUSNICKNAME(Client & client, const std::string & nick)
{
	client.send_msg("432 " + nick + " :Erroneous nickname");
	throw Protocole_error();
}

/*
ERR_NICKNAMEINUSE (433)
  "<client> <nick> :Nickname is already in use"
Returned when a NICK command cannot be successfully completed as the desired nickname is already in use on the network. The text used in the last param of this message may vary.
*/
void ERR_NICKNAMEINUSE(Client & client, const std::string & nick)
{
	client.send_msg(": 433 * " + nick + " :Nickname is already in use");
	throw Protocole_error();
}

/*
436    ERR_NICKCOLLISION
		"<nick> :Nickname collision KILL from <user>@<host>"

	- Returned by a server to a client when it detects a
	nickname collision (registered of a NICK that
	already exists by another server).

437    ERR_UNAVAILRESOURCE
		"<nick/channel> :Nick/channel is temporarily unavailable"

	- Returned by a server to a user trying to join a channel
	currently blocked by the channel delay mechanism.

	- Returned by a server to a user trying to change nickname
	when the desired nickname is blocked by the nick delay
	mechanism.
*/

/*
ERR_USERNOTINCHANNEL (441)
  "<client> <nick> <channel> :They aren't on that channel"
Returned when a client tries to perform a channel+nick affecting command, when the nick isn’t joined to the channel (for example, MODE #channel +o nick).
*/
void ERR_USERNOTINCHANNEL(Client & client, const std::string & name, const Channel & channel)
{
	client.send_msg("441 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :They aren't on that channel");
}

/*
ERR_NOTONCHANNEL (442)
  "<client> <channel> :You're not on that channel"
Returned when a client tries to perform a channel-affecting command on a channel which the client isn’t a part of.
*/
void ERR_NOTONCHANNEL(Client & client, const Channel & channel)
{
	client.send_msg("442 " + channel.get_name() + " :You're not on that channel");
	throw Protocole_error();
}

/*
ERR_USERONCHANNEL (443)
  "<client> <nick> <channel> :is already on channel"
Returned when a client tries to invite <nick> to a channel they’re already joined to.
*/
void ERR_USERONCHANNEL(Client & client, const std::string & name, const Channel & channel)
{
	client.send_msg("443 " + client.get_nickname() + " " + name + " " + channel.get_name() + " :is already on channell");
	throw Protocole_error();
}

/*
444    ERR_NOLOGIN
		"<user> :User not logged in"

	- Returned by the summon after a SUMMON command for a
	user was unable to be performed since they were not
	logged in.
*/
/*
445    ERR_SUMMONDISABLED
		":SUMMON has been disabled"

	- Returned as a response to the SUMMON command.  MUST be
	returned by any server which doesn't implement it.

446    ERR_USERSDISABLED
		":USERS has been disabled"

	- Returned as a response to the USERS command.  MUST be
	returned by any server which does not implement it.
*/

/*
ERR_NOTREGISTERED (451)
  "<client> :You have not registered"
Returned when a client command cannot be parsed as they are not yet registered. Servers offer only a limited subset of commands until clients are properly registered to the server. The text used in the last param of this message may vary.
*/
void ERR_NOTREGISTERED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 451 :You have not registered");
		throw Protocole_error();
}

/*
ERR_NEEDMOREPARAMS (461)
  "<client> <command> :Not enough parameters"
Returned when a client command cannot be parsed because not enough parameters were supplied. The text used in the last param of this message may vary.
*/
void ERR_NEEDMOREPARAMS(Client & client, const std::string & command)
{
	client.send_msg("461 " + command + " :Not enough parameters");
	throw Protocole_error();
}

/*
ERR_ALREADYREGISTERED (462)
  "<client> :You may not reregister"
Returned when a client tries to change a detail that can only be set during registration (such as resending the PASS or USER after registration). The text used in the last param of this message varies.
*/
void ERR_ALREADYREGISTRED(Client & client)
{
	client.send_msg("462 :Unauthorized command (already registered)");
	throw Protocole_error();
}

/*
463    ERR_NOPERMFORHOST
		":Your host isn't among the privileged"

	- Returned to a client which attempts to register with
	a server which does not been setup to allow
	connections from the host the attempted connection
	is tried.
*/

/*
ERR_PASSWDMISMATCH (464)
  "<client> :Password incorrect"
Returned to indicate that the connection could not be registered as the password was either incorrect or not supplied. The text used in the last param of this message may vary.
*/
void ERR_PASSWDMISMATCH(Client & client)
{
	client.send_msg("464 :Password incorrect");
	throw Protocole_error();
}

/*
465    ERR_YOUREBANNEDCREEP
		":You are banned from this server"

	- Returned after an attempt to connect and register
	yourself with a server which has been setup to
	explicitly deny connections to you.

466    ERR_YOUWILLBEBANNED

	- Sent by a server to a user to inform that access to the
	server will soon be denied.

467    ERR_KEYSET
		"<channel> :Channel key already set"
471    ERR_CHANNELISFULL
		"<channel> :Cannot join channel (+l)"
472    ERR_UNKNOWNMODE
		"<char> :is unknown mode char to me for <channel>"
*/

/*
ERR_CHANNELISFULL (471)
  "<client> <channel> :Cannot join channel (+l)"
Returned to indicate that a JOIN command failed because the client limit mode has been set and the maximum number of users are already joined to the channel. The text used in the last param of this message may vary.
*/
void ERR_CHANNELISFULL(const Client & client, const Channel & channel)
{
	client.send_msg("471 " + channel.get_name() + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*
ERR_INVITEONLYCHAN (473)
  "<client> <channel> :Cannot join channel (+i)"
Returned to indicate that a JOIN command failed because the channel is set to [invite-only] mode and the client has not been invited to the channel or had an invite exception set for them. The text used in the last param of this message may vary.
*/
void ERR_INVITEONLYCHAN(Client & client, const std::string & channel)
{
	client.send_msg("473 " + channel + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*
ERR_BANNEDFROMCHAN (474)
  "<client> <channel> :Cannot join channel (+b)"
Returned to indicate that a JOIN command failed because the client has been banned from the channel and has not had a ban exception set for them. The text used in the last param of this message may vary.
*/
void ERR_BANNEDFROMCHAN(Client & client, const std::string & channel)
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
void ERR_BADCHANNELKEY(Client & client, const std::string & channel)
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
void ERR_BADCHANMASK(Client & client, const std::string & channel)
{
	client.send_msg("476 " + channel + " :Bad Channel Mask");
	throw Protocole_error();
}

/*
477    ERR_NOCHANMODES
		"<channel> :Channel doesn't support modes"
478    ERR_BANLISTFULL
		"<channel> <char> :Channel list is full"

481    ERR_NOPRIVILEGES
		":Permission Denied- You're not an IRC operator"

	- Any command requiring operator privileges to operate
	MUST return this error to indicate the attempt was
	unsuccessful.
*/

/*
ERR_CHANOPRIVSNEEDED (482)
  "<client> <channel> :You're not channel operator"
Indicates that a command failed because the client does not have the appropriate channel privileges. This numeric can apply for different prefixes such as halfop, operator, etc. The text used in the last param of this message may vary.
*/
void ERR_CHANOPRIVSNEEDED(const Client & client, const Channel & channel)
{
	client.send_msg("482 " + channel.get_name() + " :You're not channel operator");
	throw Protocole_error();
}

/*
483    ERR_CANTKILLSERVER
		":You can't kill a server!"

	- Any attempts to use the KILL command on a server
	are to be refused and this error returned directly
	to the client.

484    ERR_RESTRICTED
		":Your connection is restricted!"

	- Sent by the server to a user upon connection to indicate
	the restricted nature of the connection (user mode "+r").

485    ERR_UNIQOPPRIVSNEEDED
		":You're not the original channel operator"

	- Any MODE requiring "channel creator" privileges MUST
	return this error if the client making the attempt is not
	a chanop on the specified channel.

491    ERR_NOOPERHOST
		":No O-lines for your host"

	- If a client sends an OPER message and the server has
	not been configured to allow connections from the
	client's host as an operator, this error MUST be
	returned.

501    ERR_UMODEUNKNOWNFLAG
		":Unknown MODE flag"

	- Returned by the server to indicate that a MODE
	message was sent with a nickname parameter and that
	the a mode flag sent was not recognized.

502    ERR_USERSDONTMATCH
		":Cannot change mode for other users"

	- Error sent to any user trying to view or change the
	user mode for a user other than themselves.
*/

/*
ERR_INVALIDMODEPARAM (696)
"<client> <target chan/user> <mode char> <parameter> :<description>"
Indicates that there was a problem with a mode parameter. Replaces various implementation-specific mode-specific numerics.
*/
void ERR_INVALIDMODEPARAM(const Client & client, const std::string & target, char mode, const std::string & parameter, const std::string & description)
{
	client.send_msg("696 " + client.get_nickname() + " " + target + " " + mode + " " + parameter + " :" + description);
	throw Protocole_error();
}
