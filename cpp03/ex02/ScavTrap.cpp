/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:58:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/26 23:10:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << BLUE "ScavTrap default constructor called.\033[0m" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << BLUE "ScavTrap " << name << " is created.\033[0m" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy)
{
	*this = copy;
	std::cout << BLUE "ScavTrap copy constructor called.\033[0m" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &copy)
{
	if (this != &copy)
		ClapTrap::operator=(copy);
	std::cout << BLUE "ScavTrap assignment operator called." << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << BLUE "ScavTrap " << name << " destructor called.\033[0m" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
	if (energyPoints > 0 && hitPoints > 0)
	{
		std::cout << "ScavTrap " << name << " run and attack " << target << ",causing " << attackDamage << " points of damage!" << std::endl;
		energyPoints--;
	}
	else
		std::cout << "ScavTrap " << name << " has no energy or HP left to attack!" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << CYAN "ScavTrap " << name << " is now in Gate Keeper mode!\033[0m" << std::endl;
}
