/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 04:22:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/28 07:41:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "FragTrap default constructor called." << std::endl;
}

FragTrap::FragTrap(const std::string name) : ClapTrap(name)
{
	this->name = name;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << name << " is created!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
	*this = copy;
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &copy)
{
	if (this != &copy)
	{
		ClapTrap::operator=(copy);
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->name << " is destroyed!" << std::endl;
}

void FragTrap::attack(const std::string &target)
{
	if (hitPoints <= 0)
	{
		std::cout << "FragTrap " << name << " can't attack, \
						no hit points left."
					<< std::endl;
		return ;
	}
	if (energyPoints <= 0)
	{
		std::cout << "FragTrap " << name << " has no energy left to attack." << std::endl;
		return ;
	}
	energyPoints--;
	std::cout << "FragTrap " << name << " attacks " << target << ",  \
		causing "
				<< attackDamage << " points of damage and be proud of it!\n"
				<< "(Energy Points left: " << energyPoints << ")" << std::endl;
}

void FragTrap::highFivesGuys()
{
	std::cout << CYAN << name << " requests a HIGH FIVE! ✋" << RESET << std::endl;
}