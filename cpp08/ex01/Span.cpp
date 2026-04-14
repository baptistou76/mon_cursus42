/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:43:06 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 15:10:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int N) : _N(N)
{
}

void Span::addNumber(int num)
{
	if (_numbers.size() >= _N)
		throw std::runtime_error("Span is full");
	_numbers.push_back(num);
}

int Span::shortestSpan()
{
	int	minSpan;
	int	span;

	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers for a span");
	std::vector<int> tmp = _numbers;
	std::sort(tmp.begin(), tmp.end());
	minSpan = tmp[1] - tmp[0];
	for (size_t i = 1; i < tmp.size() - 1; ++i)
	{
		span = tmp[i + 1] - tmp[i];
		if (span < minSpan)
			minSpan = span;
	}
	return (minSpan);
}

int Span::longestSpan()
{
	int	minVal;
	int	maxVal;

	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers for a span");
	minVal = *std::min_element(_numbers.begin(), _numbers.end());
	maxVal = *std::max_element(_numbers.begin(), _numbers.end());
	return (maxVal - minVal);
}

Span::~Span()
{
}