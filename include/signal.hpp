/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:40:09 by svogrig           #+#    #+#             */
/*   Updated: 2025/04/21 15:55:53 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <csignal>

extern volatile sig_atomic_t g_sigint;

void sigint_handler(int sig);
void sigint_handler_setup(void);
