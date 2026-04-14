/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:29 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/02 13:08:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	BitcoinExchange	btc;

	if (argc != 2)
	{
		std::cerr << "Usage: ./prog + file to open." << std::endl;
		return (1);
	}
	if (!btc.loadDatabase("data.csv"))
	{
		std::cerr << "Error: couldn't open database file." << std::endl;
		return (1);
	}
	btc.processInput(argv[1]);
	return (0);
}
