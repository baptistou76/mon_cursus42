/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:31:47 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/14 10:56:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*newZombie(std::string name)
{
	Zombie	*newZ;

	if (name.empty())
	{
		std::cout << "The new zombie must be named.\n";
		return (nullptr);
	}
	newZ = new Zombie(name);
	newZ->announce();
	return (newZ);
}
