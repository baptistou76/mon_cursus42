/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:08:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/03 22:31:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		_num = copy._num;
	return (*this);
}

RPN::~RPN()
{
}

bool RPN::isNumber(const std::string &token) const
{
	return (token.size() == 1 && std::isdigit(token[0]));
}

bool RPN::isOperator(const std::string &token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOperator(char op, int a, int b) const
{
	switch (op)
	{
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		if (b == 0)
			throw std::runtime_error("Error: division by 0 is not possible.");
		return (a / b);
	default:
		throw std::runtime_error("Error: can't find available token");
	}
}

int RPN::evaluate(const std::string &expression)
{
	int	b;
	int	a;

	std::stringstream ss(expression);
	std::string token;
	while (ss >> token)
	{
		if (isNumber(token))
			_num.push(token[0] - '0');
		else if (isOperator(token))
		{
			if (_num.size() < 2)
				throw std::runtime_error("Error: not enough number to calculate.");
			b = _num.top();
			_num.pop();
			a = _num.top();
			_num.pop();
			_num.push(applyOperator(token[0], a, b));
		}
		else
			throw std::runtime_error("Error: it's not possible to calculate.");
	}
	if (_num.size() != 1)
		throw std::runtime_error("Error: Only the result should remain in the stack to be showed.");
	return (_num.top());
}
