/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Params.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:39:55 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/26 12:52:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_HPP
# define PARAMS_HPP

# include <string>
# include <vector>
# include <ostream>
# include "utils.hpp"

class Params
{
	public:

		Params();
		Params(const std::string & str);
		Params(const Params & to_copy);
		
		~Params();

		Params & operator = (const Params & to_assign);

		int					get_nbr() const;
		const std::string &	get_param(int idx) const;
		const std::string &	get_first() const;
	
	private:

		std::vector<std::string> _params;

};

std::ostream & operator << (std::ostream & os, const Params & params);

#endif
