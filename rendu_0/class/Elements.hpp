/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Elements.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:22:54 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/31 18:26:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_HPP
# define ELEMENTS_HPP

# include <string>
# include <vector>
# include <ostream>
# include "utils.hpp"

class Elements
{
	public:

		Elements();
		Elements(const std::string & str);
		Elements(const Elements & to_copy);
		
		~Elements();

		Elements & operator = (const Elements & to_assign);

		int					get_nbr() const;
		const std::string &	get_element(int idx) const;
		const std::string &	get_first() const;
	
	private:

		std::vector<std::string> _elements;

};

std::ostream & operator << (std::ostream & os, const Elements & elements);

#endif