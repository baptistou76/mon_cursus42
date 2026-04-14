/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:22:45 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/13 19:19:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150)
{
	std::cout << "Bureaucrat: " << CYAN << name << RESET << " was just created." << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name),
	grade(grade)
{
	if (grade < 1)
		throw GradeTooHighExecption();
	if (grade > 150)
		throw GradeTooLowException();
	grade = grade;
	std::cout << "Bureaucrat: " << name << " is created with a grade of " << grade << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy)
{
	*this = copy;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &copy)
{
	if (this != &copy)
	{
		this->grade = copy.grade;
	}
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << CYAN "Bureaucrat: " << name << " is tired and go back home" RESET << std::endl;
}

const std::string &Bureaucrat::getName() const
{
	return (name);
}

int Bureaucrat::getGrade() const
{
	return (grade);
}

const char *Bureaucrat::GradeTooHighExecption::what() const throw()
{
	return (GREEN "Grade too high!" RESET);
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return (GREEN "Grade too low!" RESET);
}

void Bureaucrat::incrementGrade()
{
	if (grade <= 1)
		throw GradeTooHighExecption();
	grade--;
}

void Bureaucrat::decrementGrade()
{
	if (grade >= 150)
		throw GradeTooLowException();
	grade++;
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureau)
{
	out << RED << bureau.getName() << RESET << ", \
		bureaucrat grade "
		<< RED << bureau.getGrade() << RESET << ".";
	return (out);
}
