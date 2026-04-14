/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:12:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/28 21:27:30 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T> void printElement(const T &x)
{
	std::cout << x << std::endl;
}

template <typename T> void increment(T &elem)
{
	elem += 10;
}

void	addExclamation(std::string &str)
{
	str += "!";
}

int	main(void)
{
	int			intArray[] = {1, 2, 3, 4, 5};
	double		dblArray[] = {3.14, 2.71, 1.41};
	const int	constArray[] = {10, 20, 30};

	std::string strArray[] = {"Bonjour", "les", "amis"};
	std::cout << "== Int Array ==" << std::endl;
	::iter(intArray, 5, printElement<int>);
	std::cout << "\n";
	::iter(intArray, 5, increment<int>);
	::iter(intArray, 5, printElement<int>);
	std::cout << "\n== String Array ==" << std::endl;
	::iter(strArray, 3, printElement<std::string>);
	std::cout << "\n";
	::iter(strArray, 3, addExclamation);
	::iter(strArray, 3, printElement<std::string>);
	std::cout << "\n== Double Array ==" << std::endl;
	::iter(dblArray, 3, printElement<double>);
	std::cout << "\n";
	::iter(dblArray, 3, increment<double>);
	::iter(dblArray, 3, printElement<double>);
	// test sur un tableau const
	std::cout << "\n== Const Int Array ==" << std::endl;
	::iter(constArray, 3, printElement<int>);
	return (0);
}
