/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:06:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/18 23:15:15 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm",
	145, 137, target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy) : AForm(copy)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
	AForm::operator=(copy);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	executeCheck(executor);
	std::ofstream file((getTarget() + "_shrubbery").c_str());
	if (!file)
		throw std::runtime_error("Couldn't open file for writing");
	file << "      /\\      \n"
			"     /\\*\\     \n"
			"    /\\O\\*\\    \n"
			"   /*/\\/\\/\\   \n"
			"  /\\O\\/\\*\\/\\  \n"
			" /\\*\\/\\*\\/\\/\\ \n"
			"/\\O\\/\\/*/\\/O/\\\n"
			"      ||      \n";
	file.close();
}
