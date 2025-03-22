/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:54:05 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/22 01:49:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"

/*
ERR_NEEDMOREPARAMS (461)
  "<client> <command> :Not enough parameters"
Returned when a client command cannot be parsed because not enough parameters were supplied. The text used in the last param of this message may vary.
*/

/*
ERR_NOSUCHCHANNEL (403)
  "<client> <channel> :No such channel"
Indicates that no channel can be found for the supplied channel name. The text used in the last param of this message may vary.
*/

/*
ERR_TOOMANYCHANNELS (405)
  "<client> <channel> :You have joined too many channels"
Indicates that the JOIN command failed because the client has joined their maximum number of channels. The text used in the last param of this message may vary.
*/

/*
ERR_BADCHANNELKEY (475)
  "<client> <channel> :Cannot join channel (+k)"
Returned to indicate that a JOIN command failed because the channel requires a key and the key was either incorrect or not supplied. The text used in the last param of this message may vary.

Not to be confused with ERR_INVALIDKEY, which may be returned when setting a key.
*/

/*
ERR_BANNEDFROMCHAN (474)
  "<client> <channel> :Cannot join channel (+b)"
Returned to indicate that a JOIN command failed because the client has been banned from the channel and has not had a ban exception set for them. The text used in the last param of this message may vary.
*/

/*
ERR_CHANNELISFULL (471)
  "<client> <channel> :Cannot join channel (+l)"
Returned to indicate that a JOIN command failed because the client limit mode has been set and the maximum number of users are already joined to the channel. The text used in the last param of this message may vary.
*/

/*
ERR_INVITEONLYCHAN (473)
  "<client> <channel> :Cannot join channel (+i)"
Returned to indicate that a JOIN command failed because the channel is set to [invite-only] mode and the client has not been invited to the channel or had an invite exception set for them. The text used in the last param of this message may vary.
*/

/*
ERR_BADCHANMASK (476)
  "<channel> :Bad Channel Mask"
Indicates the supplied channel name is not a valid.

This is similar to, but stronger than, ERR_NOSUCHCHANNEL (403), which indicates that the channel does not exist, but that it may be a valid name.

The text used in the last param of this message may vary.
*/