/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:01:24 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/15 12:13:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string &name) : name(name), weapon(NULL)
{
}

HumanB::~HumanB()
{
	std::cout << this->name << " died." << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack() const
{
	if (this->weapon)
	{
		std::cout << this->name << " attacks with his " << this->weapon->getType() << std::endl;
	}
	else
		std::cout << this->name << " has no weapon" << std::endl;
}
