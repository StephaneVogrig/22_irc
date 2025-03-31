/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:05 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 20:03:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"
#include "Server.hpp"

/*
	Error Replies
	https://www.rfc-editor.org/rfc/rfc2812#section-5.2
*/

/*401*/ void ERR_NOSUCHNICK(Client & client, Server & server, const std::string & name)
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

/*403*/ void ERR_NOSUCHCHANNEL(Client & client, const std::string & channel_name)
{
	client.send_msg("403 " + channel_name + " :No such channel");
}

/*404*/ void ERR_CANNOTSENDTOCHAN(Client & client, const std::string & channel_name)
{
	client.send_msg("404 " + channel_name + "  :Cannot send to channel");
	throw Protocole_error();
}

/*405*/ void ERR_TOOMANYCHANNELS(Client & client, const std::string & channel_name)
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
412    ERR_NOTEXTTOSEND
		":No text to send"
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
421    ERR_UNKNOWNCOMMAND
		"<command> :Unknown command"

	- Returned to a registered client to indicate that the
	command sent is unknown by the server.

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

/*431*/ void ERR_NONICKNAMEGIVEN(Client & client)
{
	client.send_msg("431 :No nickname given");
	throw Protocole_error();
}

/*432*/ void ERR_ERRONEUSNICKNAME(Client & client, const std::string & nick)
{
	client.send_msg("432 " + nick + " :Erroneous nickname");
	throw Protocole_error();
}

/*433*/ void ERR_NICKNAMEINUSE(Client & client, const std::string & nick)
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

441    ERR_USERNOTINCHANNEL
		"<nick> <channel> :They aren't on that channel"

	- Returned by the server to indicate that the target
	user of the command is not on the given channel.
*/

/*442*/ void ERR_NOTONCHANNEL(Client & client, const Channel & channel)
{
	client.send_msg("442 " + channel.get_name() + " :You're not on that channel");
	throw Protocole_error();
}

/*
443    ERR_USERONCHANNEL
		"<user> <channel> :is already on channel"

	- Returned when a client tries to invite a user to a
	channel they are already on.

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

/*451*/ void ERR_NOTREGISTERED(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 451 :You have not registered");
		throw Protocole_error();
}

/*
461    ERR_NEEDMOREPARAMS
		"<command> :Not enough parameters"

	- Returned by the server by numerous commands to
	indicate to the client that it didn't supply enough
	parameters.
*/
/*461*/ void ERR_NEEDMOREPARAMS(Client & client, const std::string & command)
{
	client.send_msg("461 " + command + " :Not enough parameters");
	throw Protocole_error();
}

/*462*/ void ERR_ALREADYREGISTRED(Client & client)
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

/*464*/ void ERR_PASSWDMISMATCH(Client & client)
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
/*471*/ void ERR_CHANNELISFULL(const Client & client, const Channel & channel)
{
	client.send_msg("471 " + channel.get_name() + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*473*/ void ERR_INVITEONLYCHAN(Client & client, const std::string & channel)
{
	client.send_msg("473 " + channel + " :Cannot join channel (+i)");
	throw Protocole_error();
}

/*474*/ void ERR_BANNEDFROMCHAN(Client & client, const std::string & channel)
{
	client.send_msg("473 " + channel + " :Cannot join channel (+b)");
	throw Protocole_error();
}

/*475*/ void ERR_BADCHANNELKEY(Client & client, const std::string & channel)
{
	client.send_msg("475 " + channel + " :Cannot join channel (+k)");
	throw Protocole_error();
}

/*476*/ void ERR_BADCHANMASK(Client & client, const std::string & channel)
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

/*482*/ void ERR_CHANOPRIVSNEEDED(const Client & client, const Channel & channel)
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
