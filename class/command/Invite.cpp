/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:39:07 by gcannaud          #+#    #+#             */
/*   Updated: 2025/04/08 12:40:56 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include "Server.hpp"

Invite::Invite() : Command("Invite")
{}

Invite::~Invite()
{}

void Invite::exec(Client & client, const Params & params, Server & server)
{
    if (params.get_nbr() < 2)
    {
        ERR_NEEDMOREPARAMS(client, "INVITE");
    }
    Channel * channel = server.get_channel(params.get_param(1));
    if (channel == NULL)
        ERR_NOSUCHCHANNEL(client, params.get_param(1));
    if (!channel->is_join(client))
        ERR_NOTONCHANNEL(client, *channel);
    Client * target = server.get_client_by_name(params.get_first());
    if (target == NULL)
        ERR_NOSUCHNICK(client, server, params.get_first());
    if (channel->is_join(*target))
        ERR_USERONCHANNEL(client, params.get_param(1), *channel);
    if (channel->is_mode_invite_only() && !channel->is_operator(client))
        ERR_CHANOPRIVSNEEDED(client, *channel);
    channel->invite_client(target->get_nickname());
    RPL_INVITING(client, target->get_nickname(), *channel);
    target->send_msg(":" + client.get_nickname() + " INVITE " + target->get_nickname() + " " + channel->get_name());
}
