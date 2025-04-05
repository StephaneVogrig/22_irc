/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:19 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/01 20:40:52 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"
#include "Server.hpp"

/*
	Command responses
	https://modern.ircdocs.horse/

	previous: https://www.rfc-editor.org/rfc/rfc2812#section-5.1
*/

/*
RPL_WELCOME (001)
  "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
The first message sent after client registration, this message introduces the client to the network. The text used in the last param of this message varies wildly.

Servers that implement spoofed hostmasks in any capacity SHOULD NOT include the extended (complete) hostmask in the last parameter of this reply, either for all clients or for those whose hostnames have been spoofed. This is because some clients try to extract the hostname from this final parameter of this message and resolve this hostname, in order to discover their ‘local IP address’.

Clients MUST NOT try to extract the hostname from the final parameter of this message and then attempt to resolve this hostname. This method of operation WILL BREAK and will cause issues when the server returns a spoofed hostname.
*/
/*001*/ void RPL_WELCOME(Client & client, Server & server)
{
	client.send_msg(":" + server.get_name() + " 001 " + client.get_nickname() + " :Welcome to the Internet Relay Network");
}

/*
002	RPL_YOURHOST
		"Your host is <servername>, running version <ver>"
003	RPL_CREATED
		"This server was created <date>"
004	RPL_MYINFO
		"<servername> <version> <available user modes>
		<available channel modes>"

	- The server sends Replies 001 to 004 to a user upon
	successful registration.
*/

/*
005	RPL_BOUNCE
		"Try server <server name>, port <port number>"

	- Sent by the server to a user to suggest an alternative
	server.  This is often used when the connection is
	refused because the server is already full.
*/

/*
200	RPL_TRACELINK
		"Link <version & debug level> <destination>
		<next server> V<protocol version>
		<link uptime in seconds> <backstream sendq>
		<upstream sendq>"
201	RPL_TRACECONNECTING
		"Try. <class> <server>"
202	RPL_TRACEHANDSHAKE
		"H.S. <class> <server>"
203	RPL_TRACEUNKNOWN
		"???? <class> [<client IP address in dot form>]"
204	RPL_TRACEOPERATOR
		"Oper <class> <nick>"
205	RPL_TRACEUSER
		"User <class> <nick>"
206	RPL_TRACESERVER
		"Serv <class> <int>S <int>C <server>
		<nick!user|*!*>@<host|server> V<protocol version>"
207	RPL_TRACESERVICE
		"Service <class> <name> <type> <active type>"
208	RPL_TRACENEWTYPE
		"<newtype> 0 <client name>"
209	RPL_TRACECLASS
		"Class <class> <count>"
210	RPL_TRACERECONNECT
		Unused.
261	RPL_TRACELOG
		"File <logfile> <debug level>"
262	RPL_TRACEEND
		"<server name> <version & debug level> :End of TRACE"

	- The RPL_TRACE* are all returned by the server in
	response to the TRACE message.  How many are
	returned is dependent on the TRACE message and
	whether it was sent by an operator or not.  There
	is no predefined order for which occurs first.
	Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
	RPL_TRACEHANDSHAKE are all used for connections
	which have not been fully established and are either
	unknown, still attempting to connect or in the
	process of completing the 'server handshake'.
	RPL_TRACELINK is sent by any server which handles
	a TRACE message and has to pass it on to another
	server.  The list of RPL_TRACELINKs sent in
	response to a TRACE command traversing the IRC
	network should reflect the actual connectivity of
	the servers themselves along that path.
	RPL_TRACENEWTYPE is to be used for any connection
	which does not fit in the other categories but is
	being displayed anyway.
	RPL_TRACEEND is sent to indicate the end of the list.

211	RPL_STATSLINKINFO
		"<linkname> <sendq> <sent messages>
		<sent Kbytes> <received messages>
		<received Kbytes> <time open>"

	- reports statistics on a connection.  <linkname>
	identifies the particular connection, <sendq> is
	the amount of data that is queued and waiting to be
	sent <sent messages> the number of messages sent,
	and <sent Kbytes> the amount of data sent, in
	Kbytes. <received messages> and <received Kbytes>
	are the equivalent of <sent messages> and <sent
	Kbytes> for received data, respectively.  <time
	open> indicates how long ago the connection was
	opened, in seconds.

212	RPL_STATSCOMMANDS
		"<command> <count> <byte count> <remote count>"

	- reports statistics on commands usage.

219	RPL_ENDOFSTATS
		"<stats letter> :End of STATS report"

242	RPL_STATSUPTIME
		":Server Up %d days %d:%02d:%02d"

	- reports the server uptime.

243	RPL_STATSOLINE
		"O <hostmask> * <name>"

	- reports the allowed hosts from where user may become IRC
	operators.

221	RPL_UMODEIS
		"<user mode string>"

	- To answer a query about a client's own mode,
	RPL_UMODEIS is sent back.

234	RPL_SERVLIST
		"<name> <server> <mask> <type> <hopcount> <info>"
*/

/*
235	RPL_SERVLISTEND
		"<mask> <type> :End of service listing"

	- When listing services in reply to a SERVLIST message,
	a server is required to send the list back using the
	RPL_SERVLIST and RPL_SERVLISTEND messages.  A separate
	RPL_SERVLIST is sent for each service.  After the
	services have been listed (or if none present) a
	RPL_SERVLISTEND MUST be sent.

251	RPL_LUSERCLIENT
		":There are <integer> users and <integer>
		services on <integer> servers"
252	RPL_LUSEROP
		"<integer> :operator(s) online"
253	RPL_LUSERUNKNOWN
		"<integer> :unknown connection(s)"
254	RPL_LUSERCHANNELS
		"<integer> :channels formed"
255	RPL_LUSERME
		":I have <integer> clients and <integer>
		servers"

	- In processing an LUSERS message, the server
	sends a set of replies from RPL_LUSERCLIENT,
	RPL_LUSEROP, RPL_USERUNKNOWN,
	RPL_LUSERCHANNELS and RPL_LUSERME.  When
	replying, a server MUST send back
	RPL_LUSERCLIENT and RPL_LUSERME.  The other
	replies are only sent back if a non-zero count
	is found for them.

256	RPL_ADMINME
		"<server> :Administrative info"
257	RPL_ADMINLOC1
		":<admin info>"
258	RPL_ADMINLOC2
		":<admin info>"
259	RPL_ADMINEMAIL
		":<admin info>"

	- When replying to an ADMIN message, a server
	is expected to use replies RPL_ADMINME
	through to RPL_ADMINEMAIL and provide a text
	message with each.  For RPL_ADMINLOC1 a
	description of what city, state and country
	the server is in is expected, followed by
	details of the institution (RPL_ADMINLOC2)
	and finally the administrative contact for the
	server (an email address here is REQUIRED)
	in RPL_ADMINEMAIL.

263	RPL_TRYAGAIN
		"<command> :Please wait a while and try again."

	- When a server drops a command without processing it,
	it MUST use the reply RPL_TRYAGAIN to inform the
	originating client.
*/

/*
302	RPL_USERHOST
		":*1<reply> *( " " <reply> )"

	- Reply format used by USERHOST to list replies to
	the query list.  The reply string is composed as
	follows:

	reply = nickname [ "*" ] "=" ( "+" / "-" ) hostname

	The '*' indicates whether the client has registered
	as an Operator.  The '-' or '+' characters represent
	whether the client has set an AWAY message or not
	respectively.

303	RPL_ISON
		":*1<nick> *( " " <nick> )"

	- Reply format used by ISON to list replies to the
	query list.

301	RPL_AWAY
		"<nick> :<away message>"
305	RPL_UNAWAY
		":You are no longer marked as being away"
306	RPL_NOWAWAY
		":You have been marked as being away"

	- These replies are used with the AWAY command (if
	allowed).  RPL_AWAY is sent to any client sending a
	PRIVMSG to a client which is away.  RPL_AWAY is only
	sent by the server to which the client is connected.
	Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
	client removes and sets an AWAY message.

311	RPL_WHOISUSER
		"<nick> <user> <host> * :<real name>"
312	RPL_WHOISSERVER
		"<nick> <server> :<server info>"
313	RPL_WHOISOPERATOR
		"<nick> :is an IRC operator"
*/
/*
 RPL_ENDOFWHO (315)

  "<client> <mask> :End of WHO list"

Sent as a reply to the WHO command, this numeric indicates the end of a WHO response for the mask <mask>.

<mask> MUST be the same <mask> parameter sent by the client in its WHO message, but MAY be casefolded.

This numeric is sent after all other WHO response numerics have been sent to the client.
*/
/*315*/ void RPL_ENDOFWHO(Client & client)
{
	client.send_msg(":server 315 " + client.get_nickname() + " :End of WHO list");
}


/*
317	RPL_WHOISIDLE
		"<nick> <integer> :seconds idle"
*/

/*
318	RPL_ENDOFWHOIS
		"<nick> :End of WHOIS list"
*/
/*318*/ void RPL_ENDOFWHOIS(Client & client, const std::string & name)
{
	client.send_msg(":server 318 " + client.get_nickname() + " " + name + " :End of /WHOIS list");
}

/*
319	RPL_WHOISCHANNELS
		"<nick> :*( ( "@" / "+" ) <channel> " " )"

	- Replies 311 - 313, 317 - 319 are all replies
	generated in response to a WHOIS message.  Given that
	there are enough parameters present, the answering
	server MUST either formulate a reply out of the above
	numerics (if the query nick is found) or return an
	error reply.  The '*' in RPL_WHOISUSER is there as
	the literal character and not as a wild card.  For
	each reply set, only RPL_WHOISCHANNELS may appear
	more than once (for long lists of channel names).
	The '@' and '+' characters next to the channel name
	indicate whether a client is a channel operator or
	has been granted permission to speak on a moderated
	channel.  The RPL_ENDOFWHOIS reply is used to mark
	the end of processing a WHOIS message.

314	RPL_WHOWASUSER
		"<nick> <user> <host> * :<real name>"
369	RPL_ENDOFWHOWAS
		"<nick> :End of WHOWAS"

	- When replying to a WHOWAS message, a server MUST use
	the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
	ERR_WASNOSUCHNICK for each nickname in the presented
	list.  At the end of all reply batches, there MUST
	be RPL_ENDOFWHOWAS (even if there was only one reply
	and it was an error).

321	RPL_LISTSTART
		Obsolete. Not used.

322	RPL_LIST
		"<channel> <# visible> :<topic>"
323	RPL_LISTEND
		":End of LIST"

	- Replies RPL_LIST, RPL_LISTEND mark the actual replies
	with data and end of the server's response to a LIST
	command.  If there are no channels available to return,
	only the end reply MUST be sent.
*/

/*
RPL_CHANNELMODEIS (324)
  "<client> <channel> <modestring> <mode arguments>..."
Sent to a client to inform them of the currently-set modes of a channel. <channel> is the name of the channel. <modestring> and <mode arguments> are a mode string and the mode arguments (delimited as separate parameters) as defined in the MODE message description.
*/
/*324*/ void RPL_CHANNELMODEIS(const Client & client, const Channel & channel)
{
	client.send_msg(":" + client.get_nickname() + " 324 " + client.get_nickname() + " " + channel.get_name() + channel.get_modes());
}


/*
325	RPL_UNIQOPIS
		"<channel> <nickname>"

324	RPL_CHANNELMODEIS
		"<channel> <mode> <mode params>"
*/

/*
RPL_NOTOPIC (331)
  "<client> <channel> :No topic is set"
Sent to a client when joining a channel to inform them that the channel with the name <channel> does not have any topic set.
*/
/*331*/ void RPL_NOTOPIC(Client & client, Channel & channel)
{
	client.send_msg(":server 332 " + client.get_nickname() + " " + channel.get_name() + " :No topic is set");
}

/*
RPL_TOPIC (332)
  "<client> <channel> :<topic>"
Sent to a client when joining the <channel> to inform them of the current topic of the channel.
*/
/*332*/ void RPL_TOPIC(Client & client, Channel & channel)
{
	client.send_msg(":server 332 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic());
}

/*
RPL_TOPICWHOTIME (333)
  "<client> <channel> <nick> <setat>"
Sent to a client to let them know who set the topic (<nick>) and when they set it (<setat> is a unix timestamp). Sent after RPL_TOPIC (332).
*/
/*333*/ void RPL_TOPICWHOTIME(Client & client, Channel & channel)
{
	client.send_msg(":server 333 " + client.get_nickname() + " " + channel.get_name() + " :" + channel.get_topic_who());
}

/*
341	RPL_INVITING
		"<channel> <nick>"

	- Returned by the server to indicate that the
	attempted INVITE message was successful and is
	being passed onto the end client.
*/
/*341*/ void RPL_INVITING(Client & client, const std::string & name, Channel & channel)
{
	client.send_msg(":server 341 " + client.get_nickname() + " " + name + " " + channel.get_name());
}

/*
342	RPL_SUMMONING
		"<user> :Summoning user to IRC"

	- Returned by a server answering a SUMMON message to
	indicate that it is summoning that user.

346	RPL_INVITELIST
		"<channel> <invitemask>"
347	RPL_ENDOFINVITELIST
		"<channel> :End of channel invite list"

	- When listing the 'invitations masks' for a given channel,
	a server is required to send the list back using the
	RPL_INVITELIST and RPL_ENDOFINVITELIST messages.  A
	separate RPL_INVITELIST is sent for each active mask.
	After the masks have been listed (or if none present) a
	RPL_ENDOFINVITELIST MUST be sent.

348	RPL_EXCEPTLIST
		"<channel> <exceptionmask>"
349	RPL_ENDOFEXCEPTLIST
		"<channel> :End of channel exception list"
	- When listing the 'exception masks' for a given channel,
	a server is required to send the list back using the
	RPL_EXCEPTLIST and RPL_ENDOFEXCEPTLIST messages.  A
	separate RPL_EXCEPTLIST is sent for each active mask.
	After the masks have been listed (or if none present)
	a RPL_ENDOFEXCEPTLIST MUST be sent.

351	RPL_VERSION
		"<version>.<debuglevel> <server> :<comments>"

	- Reply by the server showing its version details.
	The <version> is the version of the software being
	used (including any patchlevel revisions) and the
	<debuglevel> is used to indicate if the server is
	running in "debug mode".

	The "comments" field may contain any comments about
	the version or further version details.
*/

/*
352	RPL_WHOREPLY
		"<channel> <user> <host> <server> <nick>
		( "H" / "G" > ["*"] [ ( "@" / "+" ) ]
		:<hopcount> <real name>"
*/
/*352*/ void RPL_WHOREPLY(Client & client, Client & target, Server & server, const std::string & channel_name)
{
	client.send_msg(":server 352 " + client.get_nickname() + " " + channel_name + " " + target.get_username() + " " + "host" + " " + server.get_name() + " " + target.get_nickname() + " H" + " :1 " + target.get_realname());
}

/*
315	RPL_ENDOFWHO
		"<name> :End of WHO list"

	- The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
	to answer a WHO message.  The RPL_WHOREPLY is only
	sent if there is an appropriate match to the WHO
	query.  If there is a list of parameters supplied
	with a WHO message, a RPL_ENDOFWHO MUST be sent
	after processing each list item with <name> being
	the item.
*/

/*
RPL_NAMREPLY (353)
  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
Sent as a reply to the NAMES command, this numeric lists the clients that are joined to <channel> and their status in that channel.

<symbol> notes the status of the channel. It can be one of the following:

("=", 0x3D) - Public channel.
("@", 0x40) - Secret channel (secret channel mode "+s").
("*", 0x2A) - Private channel (was "+p", no longer widely used today).
<nick> is the nickname of a client joined to that channel, and <prefix> is the highest channel membership prefix that client has in the channel, if they have one. The last parameter of this numeric is a list of [prefix]<nick> pairs, delimited by a SPACE character (' ', 0x20).
*/
/*353*/ void RPL_NAMREPLY(Client & client, Channel & channel)
{
	client.send_msg(":server 353 " + client.get_nickname() + " <symbol> " + channel.get_name() + " :" + channel.get_topic_who());
}

/*
RPL_ENDOFNAMES (366)
  "<client> <channel> :End of /NAMES list"
Sent as a reply to the NAMES command, this numeric specifies the end of a list of channel member names.
*/
/*366*/ void RPL_ENDOFNAMES(Client & client, Channel & channel)
{
	client.send_msg(":server 366 " + client.get_nickname() + " " + channel.get_name() + " :End of /NAMES list");
}

/*
364	RPL_LINKS
		"<mask> <server> :<hopcount> <server info>"
365	RPL_ENDOFLINKS
		"<mask> :End of LINKS list"

	- In replying to the LINKS message, a server MUST send
	replies back using the RPL_LINKS numeric and mark the
	end of the list using an RPL_ENDOFLINKS reply.

367	RPL_BANLIST
		"<channel> <banmask>"
368	RPL_ENDOFBANLIST
		"<channel> :End of channel ban list"

	- When listing the active 'bans' for a given channel,
	a server is required to send the list back using the
	RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
	RPL_BANLIST is sent for each active banmask.  After the
	banmasks have been listed (or if none present) a
	RPL_ENDOFBANLIST MUST be sent.

371	RPL_INFO
		":<string>"
374	RPL_ENDOFINFO
		":End of INFO list"

	- A server responding to an INFO message is required to
	send all its 'info' in a series of RPL_INFO messages
	with a RPL_ENDOFINFO reply to indicate the end of the
	replies.

375	RPL_MOTDSTART
		":- <server> Message of the day - "
372	RPL_MOTD
		":- <text>"
376	RPL_ENDOFMOTD
		":End of MOTD command"

	- When responding to the MOTD message and the MOTD file
	is found, the file is displayed line by line, with
	each line no longer than 80 characters, using
	RPL_MOTD format replies.  These MUST be surrounded
	by a RPL_MOTDSTART (before the RPL_MOTDs) and an
	RPL_ENDOFMOTD (after).

381	RPL_YOUREOPER
		":You are now an IRC operator"

	- RPL_YOUREOPER is sent back to a client which has
	just successfully issued an OPER message and gained
	operator status.

382	RPL_REHASHING
		"<config file> :Rehashing"

	- If the REHASH option is used and an operator sends
	a REHASH message, an RPL_REHASHING is sent back to
	the operator.

383	RPL_YOURESERVICE
		"You are service <servicename>"

	- Sent by the server to a service upon successful
	registration.

391	RPL_TIME
		"<server> :<string showing server's local time>"

	- When replying to the TIME message, a server MUST send
	the reply using the RPL_TIME format above.  The string
	showing the time need only contain the correct day and
	time there.  There is no further requirement for the
	time string.

392	RPL_USERSSTART
		":UserID   Terminal  Host"
393	RPL_USERS
		":<username> <ttyline> <hostname>"
394	RPL_ENDOFUSERS
		":End of users"
395	RPL_NOUSERS
		":Nobody logged in"

	- If the USERS message is handled by a server, the
	replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
	RPL_NOUSERS are used.  RPL_USERSSTART MUST be sent
	first, following by either a sequence of RPL_USERS
	or a single RPL_NOUSER.  Following this is
	RPL_ENDOFUSERS.
*/
