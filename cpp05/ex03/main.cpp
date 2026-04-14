/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:44:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/21 20:58:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int	main(void)
{
	Intern	randomIntern;
	AForm	*form;

	form = randomIntern.makeForm("robotomy request", "bender");
	if (form)
	{
		Bureaucrat bob("bob", 1);
		bob.signForm(*form);
		bob.executeForm(*form);
		delete (form);
	}
	form = randomIntern.makeForm("unknown form", "Target");
	delete (form);
	form = randomIntern.makeForm("presidential pardon", "Trump");
	if (form)
	{
		Bureaucrat donald("Donald", 1);
		donald.signForm(*form);
		donald.executeForm(*form);
		delete (form);
	}
	form = randomIntern.makeForm("shrubbery form", "silver hands");
	if (form)
	{
		Bureaucrat edward("edward", 15);
		edward.signForm(*form);
		edward.executeForm(*form);
		delete (form);
	}
	return (0);
}
