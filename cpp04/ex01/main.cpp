/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:50:29 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 08:02:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "WrongDog.hpp"
#include "Brain.hpp"

int	main(void)
{
	const int	size = 10;
	Animal		*animals[size];
	Dog			dog1;
	Dog			dog2;
	
	std::cout << RED "---------------- TEST WITH ARRAY OF ANIMALS -----------------" << RESET << std::endl;
	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
		animals[k] = new Dog();
		else
		animals[k] = new Cat();
	}
	for (int k = 0; k < size; k++)
	{
		delete animals[k];
	}
	std::cout << RED "---------------- TEST WITH DEEP COPY -----------------" << RESET << std::endl;
	dog1.setBrainIdea(0, "Chase the cats!!!");
	dog2 = dog1;
	std::cout << "Dog1 idea[0]: " << dog1.getBrainIdea(0) << std::endl;
	std::cout << "Dog2 idea[0]: " << dog2.getBrainIdea(0) << std::endl;
	dog2.setBrainIdea(0, "Sleep on the couch.");
	std::cout << "After modification:" << std::endl;
	std::cout << "Dog1 idea[0]: " << dog1.getBrainIdea(0) << std::endl;
	std::cout << "Dog2 idea[0]: " << dog2.getBrainIdea(0) << std::endl;
	return (0);
}
