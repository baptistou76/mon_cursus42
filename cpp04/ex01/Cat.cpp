/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:40:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 07:39:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	this->type = YELLOW "Cat" RESET;
	this->brain = new Brain();
	std::cout << YELLOW "Cat constructor is called." << RESET << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy)
{
	this->type = copy.type;
	brain = new Brain(*copy.brain);
	std::cout << YELLOW "The copycat was called !" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
		delete (brain);
		brain = new Brain(*copy.brain);
	}
	return (*this);
}

Cat::~Cat()
{
	std::cout << YELLOW "The cat is passed under a car! It's so sad..." << RESET << std::endl;
	delete (brain);
}

void Cat::makeSound() const
{
	std::cout << YELLOW "MEEOOOWWW... You're my slave now human... (This is a cat sound)" << RESET << std::endl;
}

void Cat::setBrainIdea(int index, const std::string &idea)
{
	brain->setIdeas(index, idea);
}

std::string Cat::getBrainIdea(int index) const
{
	return (brain->getIdea(index));
}
