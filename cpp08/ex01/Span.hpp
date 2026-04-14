/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:38:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 15:03:49 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <algorithm>
# include <iostream>
# include <list>
# include <stdexcept>
# include <vector>

class Span
{
  private:
	unsigned int _N;
	std::vector<int> _numbers;

  public:
	Span(unsigned int N);
	~Span();

	void addNumber(int num);
	int shortestSpan();
	int longestSpan();

	template <typename InputIt> void addNumbers(InputIt begin, InputIt end)
	{
		for (InputIt it = begin; it != end; it++)
		{
			if (_numbers.size() >= _N)
				throw std::runtime_error("Span is full");
			_numbers.push_back(*it);
		}
	}
};

#endif