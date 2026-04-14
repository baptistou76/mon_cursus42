/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:18:52 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/19 16:59:48 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	size_t	pos;

	if (argc != 4)
	{
		std::cerr << "You must have a fileName and two strings.\n" << std::endl;
		return (1);
	}
	std::string fileName = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	if (s1.empty())
	{
		std::cerr << "Error: s1 can't be empty.\n";
		return (1);
	}
	std::ifstream infile(fileName);
	if (!infile)
	{
		std::cerr << "Error: cannot open " << fileName << ".\n";
		return (1);
	}
	std::ofstream outfile(fileName + ".replace");
	if (!outfile)
	{
		std::cerr << "Error: outfile can't be created.\n" << std::endl;
		return (1);
	}
	std::string line;
	while (std::getline(infile, line))
	{
		pos = 0;
		while ((pos = line.find(s1, pos)) != std::string::npos)
		{
			line.erase(pos, s1.length());
			line.insert(pos, s2);
			pos += s2.length();
		}
		outfile << line << std::endl;
	}
	infile.close();
	outfile.close();
	return (0);
}
