/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:20:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 06:04:16 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("Wrong type")
{
	std::cout << "A wrong animal is created!" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &copy)
{
	this->type = copy.type;
	std::cout << "Wrong animal is cloned." << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &copy)
{
	if (this != &copy)
		this->type = copy.type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
}

void WrongAnimal::makeSound(void) const
{
	std::cout << "CROOOAAA, CROOOAAA !!! (This is a wrong sound, \
		isn't it?)"
				<< std::endl;
}

std::string WrongAnimal::getType() const
{
	return (this->type);
}