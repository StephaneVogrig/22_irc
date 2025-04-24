/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:27 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 16:51:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include "Params.hpp"
# include <ostream>

class Message
{
	public:

		Message(const std::string & str);
		Message(const Message & toCopy);

		~Message();

		Message & operator = (const Message & toAssign);

		const std::string &	get_prefix() const;
		const std::string &	get_command() const;
		const Params &		get_params() const;

	private:

		std::string	_prefix;
		std::string	_command;
		Params		_parameters;

		void extract_command(const std::string & str, size_t start, size_t stop);

};

std::ostream & operator << (std::ostream & os, const Message & msg);

#endif
