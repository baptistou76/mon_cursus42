/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:35:55 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/03 21:58:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <algorithm>
# include <cctype>
# include <iomanip>
# include <iostream>
# include <limits>
# include <list>
# include <map>
# include <sstream>
# include <stack>
# include <string>
# include <vector>

class RPN
{
  private:
	std::stack<int> _num;
	bool isNumber(const std::string &token) const;
	bool isOperator(const std::string &token) const;
	int applyOperator(char op, int a, int b) const;

  public:
	RPN();
	RPN(const RPN &copy);
	RPN &operator=(const RPN &copy);
	~RPN();

	int evaluate(const std::string &expression);
};

#endif