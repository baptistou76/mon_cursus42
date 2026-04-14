/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:12:42 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 14:27:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int	main(void)
{
	std::vector<int> v;
	v.push_back(5);
	v.push_back(10);
	v.push_back(15);
	try
	{
		std::vector<int>::iterator it = easyfind(v, 10);
		std::cout << "Found value: " << *it << std::endl;
		it = easyfind(v, 20);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	try
	{
		std::list<int>::iterator it = easyfind(lst, 3);
		std::cout << "Found in list: " << *it << std::endl;
		it = easyfind(lst, 5);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return (0);
}
