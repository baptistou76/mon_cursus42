/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 04:50:29 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 06:13:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "WrongDog.hpp"

int	main(void)
{
	const Animal		*meta = new Animal();
	const Animal		*i = new Dog();
	const Animal		*j = new Cat();
	const WrongAnimal	*Wmeta = new WrongAnimal();
	const WrongAnimal	*Wi = new WrongDog();
	const WrongAnimal	*Wj = new WrongCat();

	std::cout << RED "---------------- TEST WITH ANIMALS -----------------" << RESET << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << j->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();
	std::cout << RED "---------------- TEST WITH WRONGANIMALS -----------------" << RESET << std::endl;
	std::cout << Wi->getType() << " " << std::endl;
	std::cout << Wj->getType() << " " << std::endl;
	Wi->makeSound();
	Wj->makeSound();
	Wmeta->makeSound();
	delete (meta);
	delete (i);
	delete (j);
	delete (Wi);
	delete (Wmeta);
	delete (Wj);
	return (0);
}
