/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongDog.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:46:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 05:53:39 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongDog.hpp"

WrongDog::WrongDog()
{
	this->type = "WrongDog";
	std::cout << "A WrongDog is created." << std::endl;
}

WrongDog::WrongDog(const WrongDog &copy) : WrongAnimal(copy)
{
	this->type = copy.type;
	std::cout << "The WrongCopy is cloned." << std::endl;
}

WrongDog &WrongDog::operator=(const WrongDog &copy)
{
	if (this != &copy)
		this->type = copy.type;
	return (*this);
}

WrongDog::~WrongDog()
{
}
