/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:42:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/16 20:05:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"

void sigint_handler(int sig)
{
	g_sigint = sig;
}

void sigint_handler_setup(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}
