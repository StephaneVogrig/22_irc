/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:40:09 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 18:53:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

# include <csignal>

extern volatile sig_atomic_t g_sigint;

void sigint_handler_setup(void);
void sigalarm_handler_setup(void);
void sigalarm_handler_setdflt(void);

#endif
