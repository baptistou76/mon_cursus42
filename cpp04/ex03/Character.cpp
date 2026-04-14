/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:56:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/09/01 08:31:30 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const &name) : name(name)
{
	for (int i = 0; i < 4; i++)
		inventory[i] = 0;
	std::cout << "Character " << GREEN << name << RESET << " was just created!" << std::endl;
}

Character::Character(Character const &copy)
{
	for (int i = 0; i < 4; i++)
	{
		if (copy.inventory[i])
			inventory[i] = copy.inventory[i]->clone();
		else
			inventory[i] = 0;
	}
	name = copy.name;
}

Character &Character::operator=(Character const &copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < 4; i++)
		{
			if (inventory[i])
			{
				delete (inventory[i]);
				inventory[i] = 0;
			}
			if (copy.inventory[i])
				inventory[i] = copy.inventory[i]->clone();
		}
	}
	name = copy.name;
	return (*this);
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		if (inventory[i])
			delete (inventory[i]);
	}
}

std::string const &Character::getName() const
{
	return (name);
}

void Character::equip(AMateria *m)
{
	if (!m)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!inventory[i])
		{
			inventory[i] = m;
			std::cout << GREEN << name << RESET << ": equiped " << m->getType() << std::endl;
			return ;
		}
	}
	std::cout << GREEN << name << RESET << ": no space left for equip " << RED << m->getType() << RESET << std::endl;
}

void Character::unequip(int index)
{
	if (index >= 0 && index < 4)
	{
		inventory[index] = 0;
		std::cout << GREEN << name << RESET << ": remove from his inventory's slot " << RED << inventory[index] << RESET << std::endl;
	}
}

void Character::use(int index, ICharacter &target)
{
	if (index >= 0 && index < 4 && inventory[index])
	{
		inventory[index]->use(target);
		return ;
	}
}
