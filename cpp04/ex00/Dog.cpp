/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:25:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 05:58:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	this->type = GREEN "Dog" RESET;
	std::cout << GREEN "A dog is created and appeared." << RESET << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy)
{
	*this = copy;
	std::cout << GREEN "Dog copy constructor called." << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &copy)
{
	if (this != &copy)
		this->type = copy.type;
	return (*this);
}

Dog::~Dog()
{
	std::cout << GREEN "The dog's sadly passed away..." << RESET << std::endl;
}

void Dog::makeSound() const
{
	std::cout << GREEN "Woof ! Woof ! (This is the dog sound)" << RESET << std::endl;
}