/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:33:06 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 05:53:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	this->type = "WrongCat";
	std::cout << "A WrongCat is created." << std::endl;
}

WrongCat::WrongCat(const WrongCat &copy) : WrongAnimal(copy)
{
	this->type = copy.type;
	std::cout << "The Wrong copycat was called." << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &copy)
{
	if (this != &copy)
		this->type = copy.type;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "The Wrongcat was killed." << std::endl;
}
