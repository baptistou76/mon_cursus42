/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 01:15:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/09/01 08:26:06 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		storage[i] = 0;
}

MateriaSource::MateriaSource(MateriaSource const &copy) : IMateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		if (!copy.storage[i])
			storage[i] = 0;
		else
			storage[i] = copy.storage[i]->clone();
	}
}

MateriaSource &MateriaSource::operator=(MateriaSource const &copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < 4; i++)
		{
			if (storage[i])
			{
				delete (storage[i]);
				storage[i] = 0;
			}
			if (copy.storage[i])
				storage[i] = copy.storage[i]->clone();
		}
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		if (storage[i])
			delete (storage[i]);
	}
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!storage[i])
		{
			storage[i] = m->clone();
			return ;
		}
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (storage[i] && storage[i]->getType() == type)
		{
			std::cout << "Materia type: " << RED << storage[i]->getType() << RESET << " was created." << std::endl;
			return (storage[i]->clone());
		}
	}
	return (NULL);
}
