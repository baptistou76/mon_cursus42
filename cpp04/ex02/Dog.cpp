/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:25:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 06:45:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	this->type = GREEN "Dog" RESET;
	this->brain = new Brain();
	std::cout << GREEN "A dog is created and appeared." << RESET << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy)
{
	*this = copy;
	brain = new Brain(*copy.brain);
	std::cout << GREEN "Dog copy constructor called." << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
		delete (brain);
		brain = new Brain(*copy.brain);
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << GREEN "The dog's sadly passed away..." << RESET << std::endl;
	delete (brain);
}

void Dog::makeSound() const
{
	std::cout << GREEN "Woof ! Woof ! (This is the dog sound)" << RESET << std::endl;
}

void Dog::setBrainIdea(int index, const std::string &idea)
{
	brain->setIdeas(index, idea);
}

std::string Dog::getBrainIdea(int index) const
{
	return (brain->getIdea(index));
}
