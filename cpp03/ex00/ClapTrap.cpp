/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:01:38 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/26 23:04:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string &name) : name(name), hitPoints(10),
	energyPoints(10), attackDamage(0)
{
	std::cout << RED "ClapTrap " << this->name << " is created!\033[0m" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
{
	std::cout << RED "Copy constructor called.\033[0m" << std::endl;
	*this = copy;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &copy)
{
	std::cout << RED "Assignment operator called\033[0m" << std::endl;
	if (this != &copy)
	{
		this->name = copy.name;
		this->energyPoints = copy.energyPoints;
		this->hitPoints = copy.hitPoints;
		this->attackDamage = copy.attackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << RED "Destructor called\033[0m" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
	if (hitPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " can't attack, \
			no hit points left."
					<< std::endl;
		return ;
	}
	if (energyPoints <= 0)
	{
		std::cout << "ClapTrap " << name << "has no energy left to attack." << std::endl;
		return ;
	}
	energyPoints--;
	attackDamage = 0;
	std::cout << name << " attacks " << target << " and causing " << attackDamage << " points of damage!\n"
				<< "(Energy left: " << energyPoints << ")\n"
				<< "(" << target << " Hp left: " << energyPoints << ")" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (hitPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " is already destroy." << std::endl;
		return ;
	}
	hitPoints -= amount;
	if (hitPoints < 0)
		hitPoints = 0;
	std::cout << "ClapTrap " << name << " takes " << amount << " points of damage! (HP left: " << hitPoints << ")" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hitPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " can't repair, \
			it's destroyed!"
					<< std::endl;
		return ;
	}
	if (energyPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " has no energy left to repair" << std::endl;
		return ;
	}
	energyPoints--;
	hitPoints += amount;
	std::cout << "ClapTrap " << name << " repair itself, \
		recovering "
				<< amount << " hit points!\n(HP left: " << hitPoints << ")" << std::endl;
}
