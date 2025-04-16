/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:40:09 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/16 20:05:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

extern volatile sig_atomic_t g_sigint;

void sigint_handler(int sig);
void sigint_handler_setup(void);
