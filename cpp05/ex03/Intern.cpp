/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:03:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/21 20:56:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &copy)
{
	(void)copy;
}

Intern &Intern::operator=(const Intern &copy)
{
	(void)copy;
	return (*this);
}

Intern::~Intern()
{
}

AForm *Intern::createShrubbery(std::string target)
{
	return (new ShrubberyCreationForm(target));
}

AForm *Intern::createRobotomy(std::string target)
{
	return (new RobotomyRequestForm(target));
}

AForm *Intern::createPresidential(std::string target)
{
	return (new PresidentialPardonForm(target));
}

AForm *Intern::makeForm(std::string formName, std::string target)
{
	std::string formNames[3] = {"shrubbery form", "robotomy request",
		"presidential pardon"};
	AForm *(*formCreators[3])(std::string) = {&Intern::createShrubbery,
		&Intern::createRobotomy, &Intern::createPresidential};
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (formCreators[i](target));
		}
	}
	std::cerr << "Intern couldn't find the request form: " << formName << std::endl;
	return (NULL);
}
