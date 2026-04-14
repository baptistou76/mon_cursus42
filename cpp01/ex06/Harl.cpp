/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:17:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/19 17:17:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
	levels[0] = "DEBUG";
	levels[1] = "INFO";
	levels[2] = "WARNING";
	levels[3] = "ERROR";
}

Harl::~Harl()
{
}

void Harl::debug()
{
	std::cout << "[ DEBUG ]\nI have to DEBBUG this." << std::endl;
}

void Harl::info()
{
	std::cout << "[ INFO ]\nIt will rain today. This is a real info." << std::endl;
}

void Harl::warning()
{
	std::cout << "[ WARNING ]\nWarning ! Be carefull about Harl." << std::endl;
}

void Harl::error()
{
	std::cout << "[ ERROR ]\nError ! You made a mistake." << std::endl;
}

void Harl::harlFilter(std::string level)
{
	int	levelIndex;

	levelIndex = -1;
	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			levelIndex = i;
			break ;
		}
	}
	switch (levelIndex)
	{
	case 0:
		debug();
		// fall through
	case 1:
		info();
		// fall through
	case 2:
		warning();
		// fall through
	case 3:
		error();
		break ;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
}
