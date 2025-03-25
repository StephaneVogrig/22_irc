/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:27 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/25 18:33:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

class Message
{
	public:

		Message(const std::string & str);
		Message(const Message & toCopy);

		~Message();

		Message & operator = (const Message & toAssign);

		const std::string &			getPrefix();
		const std::string &			getCommand();
		std::vector<std::string> &	getParameters();

	private:

		std::string					_prefix;
		std::string					_command;
		std::vector<std::string>	_parameters;

		void extract_info(const std::string & str);
		void extract_command(const std::string & str, size_t start, size_t stop);

};

#endif
