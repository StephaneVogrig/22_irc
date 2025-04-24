/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:42:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/24 18:52:57 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"
#include <iostream>

volatile sig_atomic_t	g_sigint;

static void sigint_handler(int sig)
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

static void sigalarm_handler(int sig)
{
	(void)sig;
	throw std::runtime_error("timeout");
}

void sigalarm_handler_setup(void)
{
	struct sigaction sa;
	sa.sa_handler = sigalarm_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
}

void sigalarm_handler_setdflt(void)
{
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
}
