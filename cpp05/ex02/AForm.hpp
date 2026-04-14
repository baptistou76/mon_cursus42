/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:12:45 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/18 23:05:01 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include "Bureaucrat.hpp"
# include <iostream>
# include <stdexcept>
# include <string>

class	Bureaucrat;

class AForm
{
  private:
	const std::string name;
	bool isSigned;
	const int gradeToSign;
	const int gradeToExecute;

  protected:
	std::string target;

  public:
	AForm(std::string name, int gradeToSign, int gradeToExecute,
		std::string target);
	AForm(const AForm &copy);
	AForm &operator=(const AForm &copy);
	virtual ~AForm();

	std::string getName() const;
	std::string getTarget() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	void beSigned(Bureaucrat const &b);
	void executeCheck(Bureaucrat const &executor) const;

	virtual void execute(Bureaucrat const &executor) const = 0;
	class GradeTooHighException : public std::exception
	{
		public:
		const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
		public:
		const char *what() const throw();
	};
	class FormNotSignedException : public std::exception
	{
		public:
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif