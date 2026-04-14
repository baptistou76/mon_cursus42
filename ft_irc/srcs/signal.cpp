/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:22:56 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/13 14:27:15 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"

volatile sig_atomic_t	g_running = 1;

void	sigint_handler(int)
{
	g_running = 0;
}