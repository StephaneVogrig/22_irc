/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:40:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 13:19:13 by svogrig          ###   ########.fr       */
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
		ERR_NEEDMOREPARAMS(client, "MODE");

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
		ERR_NOSUCHCHANNEL(client, channel_name);

	if (params.get_nbr() == 1)
	{
		RPL_324_CHANNELMODEIS(client, *channel, server);
		RPL_329_CREATIONTIME(client, *channel, server);
		return ;
	}

	if (!channel->is_operator(client))
		ERR_CHANOPRIVSNEEDED(client, *channel);

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

			if (*it == 'i' || *it == 't')
			{
				if (action == '+')
					channel->set_mode(client, *it);
				if (action == '-')
					channel->unset_mode(*it);
			}
			else if (*it == 'k')
			{
				if (action == '+')
				{
					if (i >= params.get_nbr())
						ERR_NEEDMOREPARAMS(client, _name);
					mode_param = params.get_param(i++);
					channel->set_key(mode_param);
					channel->set_mode(client, *it);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else if (*it == 'o')
			{
				if (i >= params.get_nbr())
					ERR_NEEDMOREPARAMS(client, _name);
				mode_param = params.get_param(i++);

				Client * target = server.get_client_by_name(mode_param);

				if (target == NULL)
					ERR_NOSUCHNICK(client, server, mode_param);

				if (!channel->is_join(*target))
					ERR_USERNOTINCHANNEL(client, target->get_nickname(), *channel);

				if (action == '+')
				{
					channel->set_client_status(*target, *it);
					channel->set_key(mode_param);
				}
				if (action == '-')
					channel->unset_client_status(*target, *it);
			}
			else if (*it == 'l')
			{
				if (action == '+')
				{
					if (i >= params.get_nbr())
						ERR_NEEDMOREPARAMS(client, _name);
					mode_param = params.get_param(i++);
					char *		endptr = NULL;
					long int	nbr = strtol(mode_param.c_str(), &endptr, 10);
					if (*endptr != '\0' || nbr < 0 || nbr > INT_MAX)
						ERR_INVALIDMODEPARAM(client, channel->get_name(), *it, mode_param, "invalid number");
					channel->set_mode(client, *it);
					channel->set_limit(nbr);
				}
				if (action == '-')
					channel->unset_mode(*it);
			}
			else
				ERR_UNKNOWNMODE(client, *it);

			mode_rpl.add_mode(action, *it, mode_param);
		}
		catch(const Protocole_error& e)
		{}
		catch(const Server::Client_not_found& e)
		{
			ERR_NOSUCHNICK(client, server, "");
		}
	}
	log("mode_rpl: " + mode_rpl.get_mode_rpl());
	channel->send_msg_by_client(client, "MODE " + channel->get_name() + " " + mode_rpl.get_mode_rpl());
	log("modestring: " + channel->get_modes() + " limit: " + to_string(channel->get_limit_clients()) + " key: " + channel->get_key());
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
		ERR_NOSUCHNICK(client, server, params.get_first());
	}
}
