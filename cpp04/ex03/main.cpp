/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:09:20 by bcaumont          #+#    #+#             */
/*   Updated: 2025/09/01 08:28:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int	main(void)
{
	IMateriaSource	*src;
	ICharacter		*me;
	AMateria		*tmp;
	ICharacter		*bob;

	src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	me = new Character("me");
	tmp = src->createMateria("ice");
	me->equip(tmp);
	me->unequip(0);
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete (bob);
	delete (me);
	delete (src);
	return (0);
}
