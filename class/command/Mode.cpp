/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:40:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 21:34:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"
#include "Mode_rpl.hpp"

Mode::Mode(void) : Command("MODE")
{}

Mode::~Mode(void)
{}

void Mode::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() == 0)
		ERR_461_NEEDMOREPARAMS(client, "MODE");

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		exec_on_user(client, params, server);
}

void Mode::exec_on_channel(Client & client, const Params & params, Server & server)
{
	const std::string & channel_name = params.get_first();

	Channel * channel = server.get_channel(channel_name);
	if (channel == NULL)
		ERR_403_NOSUCHCHANNEL(client, channel_name);

	if (params.get_nbr() == 1)
	{
		RPL_324_CHANNELMODEIS(client, *channel, server);
		RPL_329_CREATIONTIME(client, *channel, server);
		return ;
	}

	if (!channel->is_operator(client))
		ERR_482_CHANOPRIVSNEEDED(client, *channel);

	std::string modestring = params.get_param(1);

	int i = 2;

	char action = '\0';
	Mode_rpl mode_rpl;

	for (std::string::iterator it = modestring.begin(); it != modestring.end(); ++it)
	{
		try
		{
			std::string mode_param = "";
			if(*it == '+' || *it == '-')
			{
				action = *it;
				continue ;
			}

			if (*it == 'i')
			{
				if (action == '+')
				{
					if (channel->is_mode_invite_only())
						ERR_467_KEYSET(client, *channel);
					channel->set_mode(*it);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else if (*it == 't')
			{
				if (action == '+')
				{
					if (channel->is_mode_protected_topic())
						ERR_467_KEYSET(client, *channel);
					channel->set_mode(*it);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else if (*it == 'k')
			{
				if (action == '+')
				{
					if (i >= params.get_nbr())
						ERR_461_NEEDMOREPARAMS(client, _name);
					mode_param = params.get_param(i++);
					if (channel->get_key() == mode_param && channel->is_mode_key_needed())
						ERR_467_KEYSET(client, *channel);

					channel->set_key(mode_param);
					channel->set_mode(*it);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else if (*it == 'o')
			{
				if (i >= params.get_nbr())
					ERR_461_NEEDMOREPARAMS(client, _name);
				mode_param = params.get_param(i++);

				Client * target = server.get_client_by_name(mode_param);

				if (target == NULL)
					ERR_401_NOSUCHNICK(client, server, mode_param);

				if (!channel->is_join(*target))
					ERR_441_USERNOTINCHANNEL(client, target->get_nickname(), *channel);

				if (action == '+')
				{
					channel->set_client_status(*target, *it);
				}
				if (action == '-')
					channel->unset_client_status(*target, *it);
			}
			else if (*it == 'l')
			{
				if (action == '+')
				{
					if (i >= params.get_nbr())
						ERR_461_NEEDMOREPARAMS(client, _name);
					mode_param = params.get_param(i++);
					char *		endptr = NULL;
					long int	nbr = strtol(mode_param.c_str(), &endptr, 10);
					if (*endptr != '\0' || nbr < 0 || nbr > INT_MAX)
						ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, mode_param, "invalid number");
					if (channel->get_limit_clients() == nbr && channel->is_mode_limit_clients())
						ERR_467_KEYSET(client, *channel);

					channel->set_mode(*it);
					channel->set_limit(nbr);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else
				ERR_472_UNKNOWNMODE(client, *it);

			mode_rpl.add_mode(action, *it, mode_param);
		}
		catch(const Protocole_error& e)
		{}
		catch(const Server::Client_not_found& e)
		{
			ERR_401_NOSUCHNICK(client, server, "");
		}
	}
	if (!mode_rpl.is_empty())
		channel->send_msg(client.get_nickname(), "MODE " + channel->get_name() + " " + mode_rpl.get_mode_rpl());
}

void Mode::exec_on_user(Client & client, const Params & params, Server & server)
{
	(void)client;
	(void)params;
	(void)server;
	try
	{
		Client * target = server.get_client_by_name(params.get_first());
		(void)target;
	}
	catch(const Server::Client_not_found & e)
	{
		ERR_401_NOSUCHNICK(client, server, params.get_first());
	}
}
