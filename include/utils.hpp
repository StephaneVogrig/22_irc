/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:20:20 by svogrig           #+#    #+#             */
/*   Updated: 2025/03/29 01:50:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#define RESET			"\033[0m"

// foreground colors
#define FG_BLACK		"\033[30m"
#define FG_RED			"\033[31m"
#define FG_GREEN		"\033[32m"
#define FG_YELLOW		"\033[33m"
#define FG_BLUE			"\033[34m"
#define FG_PURPLE		"\033[35m"
#define FG_CYAN			"\033[36m"
#define FG_WHITE		"\033[37m"
#define FG_DEFAULT		"\033[39m"

// background colors
#define BG_BLACK		"\033[40m"
#define BG_RED			"\033[41m"
#define BG_GREEN		"\033[42m"
#define BG_YELLOW		"\033[43m"
#define BG_BLUE			"\033[44m"
#define BG_PURPLE		"\033[45m"
#define BG_CYAN			"\033[46m"
#define BG_WHITE		"\033[47m"
#define BG_DEFAULT		"\033[49m"

// color with effect
#define PURPLE_BLINK	"\033[5;35m"
#define GREEN_BLINK		"\033[5;32m"

// effect
#define BOLD_ON			"\033[1m"
#define DIM_ON			"\033[2m"
#define UNDERLINED_ON	"\033[4m"
#define BLINK_ON		"\033[5m"
#define REVERSE_ON		"\033[7m"
#define HIDE_ON			"\033[8m"

#define BOLD_OFF		"\033[21m"
#define DIM_OFF			"\033[21m"
#define UNDERLINED_OFF	"\033[24m"
#define BLINK_OFF		"\033[25m"
#define REVERSE_OFF		"\033[27m"
#define HIDE_OFF		"\033[28m"
#define ERASE_LINE		"\033[K"

#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include <iomanip>

template<typename T>
std::string to_string(const T & value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename T>
std::string to_string_right(const T & value, int witdh, char c)
{
	std::ostringstream oss;
	oss << std::setfill(c) << std::setw(witdh) << std::right << value;
	return oss.str();
}

template<typename T>
std::string to_string_left(const T & value, int witdh, char c)
{
	std::ostringstream oss;
	oss << std::setfill(c) << std::setw(witdh) << std::left << value;
	return oss.str();
}

struct tm * current_time();
std::string tm_to_time_str(struct tm * timeinfo);
std::string current_time_str();
std::string current_date_str();

#endif
