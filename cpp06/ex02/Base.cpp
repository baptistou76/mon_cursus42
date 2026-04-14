/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:20:14 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/24 21:15:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base()
{
}

Base	*generate(void)
{
	int	r;

	std::srand(std::time(NULL));
	r = std::rand() % 3;
	if (r == 0)
	{
		std::cout << "Generate type: A" << std::endl;
		return (new A);
	}
	else if (r == 1)
	{
		std::cout << "Generate type: B" << std::endl;
		return (new B);
	}
	else
	{
		std::cout << "Generate type: C" << std::endl;
		return (new C);
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "Type: A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "Type: B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "Type: C" << std::endl;
	else
		std::cout << "Type: Unknown" << std::endl;
}

void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "Type: A" << std::endl;
		return ;
	}
	catch (std::exception &)
	{
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "Type: B" << std::endl;
		return ;
	}
	catch (const std::exception &)
	{
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "Type: C" << std::endl;
	}
	catch (const std::exception &)
	{
	}
	std::cout << "Type: Unknown" << std::endl;
}
