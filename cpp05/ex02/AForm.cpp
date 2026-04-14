/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:17:58 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/18 20:01:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute,
	std::string target) : name(name), isSigned(false), gradeToSign(gradeToSign),
	gradeToExecute(gradeToExecute), target(target)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::~AForm()
{
	std::cout << name << " is destoyed !" << std::endl;
}

AForm::AForm(const AForm &copy) : name(copy.name), isSigned(copy.isSigned),
	gradeToSign(copy.gradeToSign), gradeToExecute(copy.gradeToExecute),
	target(copy.target)
{
}

AForm &AForm::operator=(const AForm &copy)
{
	if (this != &copy)
		this->isSigned = copy.isSigned;
	return (*this);
}

std::string AForm::getName() const
{
	return (name);
}

bool AForm::getIsSigned() const
{
	return (isSigned);
}

int AForm::getGradeToSign() const
{
	return (gradeToSign);
}

int AForm::getGradeToExecute() const
{
	return (gradeToExecute);
}

std::string AForm::getTarget() const
{
	return (target);
}

void AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > gradeToSign)
		throw GradeTooLowException();
	isSigned = true;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed!");
}

void AForm::executeCheck(const Bureaucrat &executor) const
{
	if (!isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > gradeToExecute)
		throw GradeTooLowException();
}

std::ostream &operator<<(std::ostream &out, const AForm &form)
{
	out << "Form " << form.getName() << ",\
		signed: "
		<< (form.getIsSigned() ? "yes" : "no") << ",\
		grade to sign : "
		<< form.getGradeToSign() << ",\
		grade to execute : "
		<< form.getGradeToExecute();
	return (out);
}
