/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:41:32 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 05:57:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Unknown")
{
	std::cout << CYAN "Animal default constructor called." << RESET << std::endl;
}

Animal::Animal(const Animal &copy)
{
	*this = copy;
	std::cout << CYAN "Animal copy constructor called." << RESET << std::endl;
}

Animal &Animal::operator=(const Animal &copy)
{
	if (this != &copy)
		this->type = copy.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << CYAN "Animal destructor called." << RESET << std::endl;
}

void Animal::makeSound() const
{
	std::cout << CYAN "Animal makes a generic sound..." << RESET << std::endl;
}

std::string Animal::getType() const
{
	return (this->type);
}
