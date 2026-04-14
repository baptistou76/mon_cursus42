/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:57:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/15 21:05:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : name(name),
	isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighExecption();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
	std::cout << "Form: " << name << " is created (sign:" << gradeToSign << ", \
		exec:" << gradeToExecute
				<< ")" << std::endl;
}

Form::Form(const Form &copy) : name(copy.name), isSigned(copy.isSigned),
	gradeToSign(copy.gradeToSign), gradeToExecute(copy.gradeToExecute)
{
}

Form &Form::operator=(const Form &copy)
{
	if (this != &copy)
		this->isSigned = copy.isSigned;
	return (*this);
}

Form::~Form()
{
	std::cout << "Form: " << name << " is destroyed !" << std::endl;
}

std::string Form::getName() const
{
	return (name);
}

bool Form::getIsSigned() const
{
	return (isSigned);
}

int Form::getGradeToSigned() const
{
	return (gradeToSign);
}

int Form::getGradeToExecute() const
{
	return (gradeToExecute);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->gradeToSign)
		throw GradeTooLowException();
	this->isSigned = true;
}

const char *Form::GradeTooHighExecption::what() const throw()
{
	return ("Grade to high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade to low!");
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << form.getName() << ", \
		form is "
		<< (form.getIsSigned() ? " signed " : " not signed ") << ", \
		grade to sign : "
		<< form.getGradeToSigned() << ", \
			grade to execute : "
		<< form.getGradeToExecute() << ".";
	return (out);
}
