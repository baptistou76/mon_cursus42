/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:58:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/25 00:00:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	std::string playerName;
	std::string ennemyName;
	std::string command;
	while (true)
	{
		std::cout << CYAN "Welcome! You have to enter a name for your ClapTrap:\n\033[0m";
		if (!std::getline(std::cin, playerName))
			return (1);
		if (!playerName.empty())
			break ;
		std::cout << "Name cannot be empty! Try again.\n";
	}
	while (true)
	{
		std::cout << CYAN "Now you have to enter a name for your target:\n\033[0m";
		if (!std::getline(std::cin, ennemyName))
			return (1);
		if (!ennemyName.empty())
			break ;
		std::cout << RED "Name cannot be empty! Try again.\n\033[0m";
	}
	ClapTrap player(playerName);
	ClapTrap ennemy(ennemyName);
	std::cout << YELLOW "OKAY DUDE !!! Let's play !!\033[0m" << std::endl;
	while (std::cin)
	{
		std::cout << GREEN "You have to enter a command:\n-1 for ATTACK\n-2 for Take Damage\n-3 for Repair your self\n-4 for quit the game.\nMake your choice: \033[0m";
		if (!std::getline(std::cin, command))
			break ;
		if (command == "1")
			player.attack(ennemyName);
		else if (command == "2")
			player.takeDamage(1);
		else if (command == "3")
			player.beRepaired(1);
		else if (command == "4")
		{
			std::cout << "Bye bye !!" << std::endl;
			break ;
		}
		else
			std::cout << "Invalid choice, you've got only 4 choices!\n";
	}
	return (0);
}
