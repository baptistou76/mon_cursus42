/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:37:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/04 00:54:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <list>
# include <sstream>
# include <stdexcept>
# include <string>
# include <vector>

class PmergeMe
{
  private:
	std::vector<int> vec;
	std::list<int> lst;

	std::vector<int> fordJohnsonVector(std::vector<int> &v);
	std::list<int> fordJohnsonList(std::list<int> &l);
	template <typename Container> void displayContainer(const Container &c) const
	{
		for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

  public:
	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe &operator=(const PmergeMe &copy);
	~PmergeMe();

	void parseInput(int argc, char **argv);
	void process();
	void generateRandom(int n);
};

#endif