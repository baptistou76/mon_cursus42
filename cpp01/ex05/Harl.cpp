/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:15:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/18 19:47:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
	levels[0] = "DEBUG";
	levels[1] = "INFO";
	levels[2] = "WARNING";
	levels[3] = "ERROR";
	complaints[0] = &Harl::debug;
	complaints[1] = &Harl::info;
	complaints[2] = &Harl::warning;
	complaints[3] = &Harl::error;
}

Harl::~Harl()
{
}

void Harl::complain(std::string level)
{
	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			(this->*complaints[i])();
			return ;
		}
	}
	std::cout << "Harl is silent..." << std::endl;
}

void Harl::debug()
{
	std::cout << "I have to DEBBUG this." << std::endl;
}

void Harl::info()
{
	std::cout << "It will rain today. This is a real info." << std::endl;
}

void Harl::warning()
{
	std::cout << "Warning ! Be carefull about Harl." << std::endl;
}

void Harl::error()
{
	std::cout << "Error ! You made a mistake." << std::endl;
}
