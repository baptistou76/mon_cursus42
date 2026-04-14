/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:58:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/28 07:41:02 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int	main(void)
{
	DiamondTrap dt("Monster");
	dt.attack("enemy");
	dt.guardGate();
	dt.highFivesGuys();
	dt.whoAmI();
	return (0);
}
