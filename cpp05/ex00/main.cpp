/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:24:57 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/13 20:53:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	try
	{
		Bureaucrat b1("Boba", 2);
		Bureaucrat b2("Coco", 149);
		std::cout << b1 << std::endl;
		std::cout << b2 << std::endl;
		b1.incrementGrade();
		std::cout << b1 << std::endl;
		b2.decrementGrade();
		std::cout << b2 << std::endl;
		b1.incrementGrade();
		std::cout << b1 << std::endl;
		b2.decrementGrade();
		std::cout << b2 << std::endl;
		b2.decrementGrade();
		std::cout << b2 << std::endl;
	}
	catch (std::exception &except)
	{
		std::cerr << "Exception caught: " << except.what() << std::endl;
	}
	try
	{
		Bureaucrat b3("Charlie", 0);
		std::cout << b3 << std::endl;
	}
	catch (std::exception &except)
	{
		std::cerr << "Exception caught: " << except.what() << std::endl;
	}
	try
	{
		Bureaucrat b4("David", 200);
	}
	catch (std::exception &except)
	{
		std::cerr << "Exception caught: " << except.what() << std::endl;
	}
	try
	{
		Bureaucrat b5("Davidou", 200);
	}
	catch (std::exception &except)
	{
		std::cerr << "Exception caught: " << except.what() << std::endl;
	}
	return (0);
}
