/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_rpl.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 03:28:41 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/08 19:30:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_PRL_HPP
# define MODE_PRL_HPP

# include <string>

class Mode_rpl
{
	public:

		Mode_rpl();
		Mode_rpl(const Mode_rpl & to_copy);

		~Mode_rpl();

		Mode_rpl & operator = (const Mode_rpl & to_assign);

		std::string get_mode_rpl();

		bool is_empty();
		void add_mode(char action, char mode, const std::string & param);

	private:

		char _current_action;
		std::string _modes;
		std::string _params;

};

#endif