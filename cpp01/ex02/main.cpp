/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 08:26:42 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/15 08:51:49 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main(void)
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;
	std::cout << "The adress of str: " << &str << std::endl;
	std::cout << "The adress of stringPTR: " << stringPTR << std::endl;
	std::cout << "The adress of stringREF: " << &stringREF << std::endl;
	std::cout << "Value of str: " << str << std::endl;
	std::cout << "Value of stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value of stringPTR: " << stringREF << std::endl;
	return (0);
}
