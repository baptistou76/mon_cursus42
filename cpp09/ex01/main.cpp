/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:17:24 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/03 22:22:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
		RPN rpn;
	int	result;

	if (argc != 2)
	{
		std::cerr << "Error: Usage: ./RPN + \"arg\"" << std::endl;
		return (1);
	}
	try
	{
		result = rpn.evaluate(argv[1]);
		std::cout << result << std::endl;
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
