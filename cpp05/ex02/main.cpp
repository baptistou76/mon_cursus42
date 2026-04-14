/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:07:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/18 23:03:23 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int	main(void)
{
	try
	{
		Bureaucrat bob("Bob", 1);
		Bureaucrat jim("Jim", 140);
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("Marvin");
		PresidentialPardonForm pardon("Arthur Dent");
		jim.signForm(shrub);
		bob.executeForm(shrub);
		bob.signForm(robot);
		bob.executeForm(robot);
		bob.signForm(pardon);
		bob.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
