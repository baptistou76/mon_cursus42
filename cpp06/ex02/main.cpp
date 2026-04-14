/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 21:03:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/24 21:10:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base	*generate(void);
void	identify(Base *p);
void	identify(Base &p);

int	main(void)
{
	Base	*base;

	base = generate();
	std::cout << "--- Identify by pointer ---" << std::endl;
	identify(base);
	std::cout << "--- Identify by reference ---" << std::endl;
	identify(*base);
	delete (base);
	return (0);
}
