/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:39:07 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/23 19:24:22 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

Invite::Invite() : Command("INVITE")
{}

Invite::~Invite()
{}

void Invite::exec(Client & client, const Params & params, Server & server)
{
    if (params.get_nbr() < 2)
        ERR_461_NEEDMOREPARAMS(client, _name, server);

    Channel * channel = server.get_channel(params.get_param(1));
    if (channel == NULL)
        ERR_403_NOSUCHCHANNEL(client, params.get_param(1), server);

    if (!channel->is_join(client))
        ERR_442_NOTONCHANNEL(client, *channel, server);

    Client * target = server.get_client_by_name(params.get_first());
    if (target == NULL)
        ERR_401_NOSUCHNICK(client, server, params.get_first());

    if (channel->is_join(*target))
        ERR_443_USERONCHANNEL(client, params.get_param(0), *channel, server);

    if (channel->is_mode_invite_only() && !channel->is_operator(client))
        ERR_482_CHANOPRIVSNEEDED(client, *channel, server);

    channel->invite_client(*target);
    RPL_341_INVITING(client, target->get_nickname(), *channel, server);
    target->send_msg(":" + client.get_nickname() + " " + _name + " " + target->get_nickname() + " " + channel->get_name());
}
