/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:40:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/23 19:18:35 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

Mode::Mode(void) : Command("MODE")
{}

Mode::~Mode(void)
{}

void Mode::exec(Client & client, const Params & params, Server & server)
{
	if (params.get_nbr() == 0)
		ERR_461_NEEDMOREPARAMS(client, _name, server);

	if (Channel::is_a_valid_name(params.get_first()))
		exec_on_channel(client, params, server);
	else
		ERR_476_BADCHANMASK(client, params.get_first(), server);
}

void Mode::exec_on_channel(Client & client, const Params & params, Server & server)
{
	const std::string & channel_name = params.get_first();

	Channel * channel = server.get_channel(channel_name);
	if (channel == NULL)
		ERR_403_NOSUCHCHANNEL(client, channel_name, server);

	if (params.get_nbr() == 1)
	{
		RPL_324_CHANNELMODEIS(client, *channel, server);
		RPL_329_CREATIONTIME(client, *channel, server);
		return ;
	}

	if (!channel->is_operator(client))
		ERR_482_CHANOPRIVSNEEDED(client, *channel, server);

	std::string modestring = params.get_param(1);

	int param_num = 2;

	char action = '+';
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
						ERR_467_KEYSET(client, *channel, server, *it);
					channel->set_mode(*it);
				}
				else
					channel->unset_mode(*it);
			}
			else if (*it == 't')
			{
				if (action == '+')
				{
					if (channel->is_mode_protected_topic())
						ERR_467_KEYSET(client, *channel, server, *it);
					channel->set_mode(*it);
				}
				else
					channel->unset_mode(*it);
			}
			else if (*it == 'k')
			{
				if (param_num >= params.get_nbr())
					ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, "*", "you must specify a parameter for the key mode", server);

				mode_param = params.get_param(param_num++);

				if (action == '+')
				{
					if (channel->is_mode_key_needed())
						ERR_467_KEYSET(client, *channel, server, *it);

					if (mode_param.find(' ') != std::string::npos)
						ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, mode_param, "parameter invalid (despite Gael's wishes)", server);

					channel->set_mode(*it);
					channel->set_key(mode_param);
				}
				else
				{
					if (channel->get_key() != mode_param)
						throw Protocole_error();
					channel->unset_mode(*it);
				}
			}
			else if (*it == 'o')
			{
				if (param_num >= params.get_nbr())
					ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, "*", "you must specify a parameter for the operator mode", server);

				mode_param = params.get_param(param_num++);

				Client * target = server.get_client_by_name(mode_param);

				if (target == NULL)
					ERR_401_NOSUCHNICK(client, server, mode_param);

				if (!channel->is_join(*target))
					ERR_441_USERNOTINCHANNEL(client, target->get_nickname(), *channel, server);

				if (action == '+')
					channel->set_client_status(*target, *it);
				else
					channel->unset_client_status(*target, *it);
			}
			else if (*it == 'l')
			{
				if (action == '+')
				{
					if (param_num >= params.get_nbr())
						ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, "*", "you must specify a parameter for the limit mode", server);

					mode_param = params.get_param(param_num++);
					int	nbr;
					std::stringstream str_stream(mode_param.c_str());
					str_stream >> nbr;
					if (str_stream.fail() || !str_stream.eof() || nbr < 0)
						ERR_696_INVALIDMODEPARAM(client, channel->get_name(), *it, mode_param, "invalid number", server);

					if (channel->get_limit_nbr_client() == nbr && channel->is_mode_limit_nbr_client())
						ERR_467_KEYSET(client, *channel, server, *it);

					if (!channel->is_mode_limit_nbr_client())
						channel->set_mode(*it);
					channel->set_limit(nbr);
				}
				else
					channel->unset_mode(*it);
			}
			else
				ERR_472_UNKNOWNMODE(client, *it, server);

			mode_rpl.add_mode(action, *it, mode_param);
		}
		catch(const Protocole_error& e)
		{}
	}
	if (!mode_rpl.is_empty())
		channel->send_to_all(client.get_nickname(), _name + " " + channel->get_name() + " " + mode_rpl.get_mode_rpl());
}
