/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:58:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/27 01:57:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int	main(void)
{
	std::string playerName;
	std::string ennemyName;
	std::string Fragtype;
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
		std::cout << CYAN "And now! You have to enter a name for your ScavTrap:\n\033[0m";
		if (!std::getline(std::cin, ennemyName))
			return (1);
		if (!playerName.empty())
			break ;
		std::cout << "Name cannot be empty! Try again.\n";
	}
	while (true)
	{
		std::cout << CYAN "Now you have to enter a name for your FragTrap:\n\033[0m";
		if (!std::getline(std::cin, Fragtype))
			return (1);
		if (!ennemyName.empty())
			break ;
		std::cout << RED "Name cannot be empty! Try again.\n\033[0m";
	}
	ClapTrap player(playerName);
	ScavTrap ennemy(ennemyName);
	FragTrap Frag(Fragtype);
	std::cout << YELLOW "OKAY DUDE !!! Let's play !!\033[0m" << std::endl;
	while (std::cin)
	{
		std::cout << GREEN "You have to enter a command:\n-1 for ATTACK\n-2 for Take Damage\n-3 for Repair your self\n-4 for activate the Gate Keeper mode.\n-5 for attack with ClapTrap\n-6 for take damage with ClapTrap\n-7 for repaired with ClapTrap\n-8 for high five guys\n-9 for attack with FragTrap\n-10 for take dammages with FragTrap\n-11 for repaired with FragTrap\n-12 for quit the game.\nMake your choice: \033[0m";
		if (!std::getline(std::cin, command))
			break ;
		if (command == "1")
			player.attack(ennemyName);
		else if (command == "2")
			player.takeDamage(1);
		else if (command == "3")
			player.beRepaired(1);
		else if (command == "4")
			ennemy.guardGate();
		else if (command == "5")
			ennemy.attack(playerName);
		else if (command == "6")
			ennemy.takeDamage(1);
		else if (command == "7")
			ennemy.beRepaired(1);
		else if (command == "8")
			Frag.highFivesGuys();
		else if (command == "9")
			Frag.attack(playerName);
		else if (command == "10")
			Frag.takeDamage(1);
		else if (command == "11")
			Frag.beRepaired(1);
		else if (command == "12")
		{
			std::cout << "Bye bye !!" << std::endl;
			break ;
		}
		else
			std::cout << "Invalid choice, you've got only 12 choices!\n";
	}
	return (0);
}
