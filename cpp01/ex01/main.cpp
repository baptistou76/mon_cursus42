/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:06:35 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/15 07:42:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(int argc, char **argv)
{
	int		N;
	char	*name;
	Zombie	*horde;

	if (argc != 3 || argv[1][0] == '\0' || argv[2][0] == '\0')
	{
		std::cout << "You must enter a number of zombie and their name.\n";
		return (1);
	}
	N = std::atoi(argv[1]);
	if (N <= 0)
	{
		std::cout << "Error: N must be higher than '0'.\n";
		return (1);
	}
	if (std::isspace(argv[2][0]))
	{
		std::cout << "The first character can't be a space.\n";
		return (1);
	}
	name = argv[2];
	horde = zombieHorde(N, name);
	for (int i = 0; i < N; i++)
	{
		horde[i].announce();
	}
	delete[] horde;
	return (0);
}
