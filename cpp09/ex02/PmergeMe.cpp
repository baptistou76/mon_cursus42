/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:02:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/04 00:55:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		this->vec = copy.vec;
		this->lst = copy.lst;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::parseInput(int argc, char **argv)
{
	long	num;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		for (size_t j = 0; j < arg.size(); ++j)
			if (!isdigit(arg[j]))
				throw std::invalid_argument("Error: no digits detected");
		std::stringstream ss(arg);
		ss >> num;
		if (ss.fail() || !ss.eof() || num < 0)
			throw std::invalid_argument("Error: negative digit detected");
		vec.push_back(static_cast<int>(num));
		lst.push_back(static_cast<int>(num));
	}
	if (vec.empty())
		throw std::invalid_argument("Error: vector is empty");
}

std::vector<int> PmergeMe::fordJohnsonVector(std::vector<int> &v)
{
	int	a;
	int	b;

	if (v.size() <= 1)
		return (v);
	std::vector<int> leaders, followers;
	for (size_t i = 0; i + 1 < v.size(); i += 2)
	{
		a = v[i];
		b = v[i + 1];
		if (a < b)
			std::swap(a, b);
		leaders.push_back(a);
		followers.push_back(b);
	}
	if (v.size() % 2 != 0)
		followers.push_back(v.back());
	leaders = fordJohnsonVector(leaders);
	for (size_t i = 0; i < followers.size(); ++i)
	{
		std::vector<int>::iterator pos = std::lower_bound(leaders.begin(),
				leaders.end(), followers[i]);
		leaders.insert(pos, followers[i]);
	}
	return (leaders);
}

std::list<int> PmergeMe::fordJohnsonList(std::list<int> &l)
{
	int	a;
	int	b;

	if (l.size() <= 1)
		return (l);
	std::list<int> leaders, followers;
	std::list<int>::iterator it = l.begin();
	while (it != l.end())
	{
		a = *it;
		++it;
		if (it == l.end())
		{
			followers.push_back(a);
			break ;
		}
		b = *it;
		if (a < b)
			std::swap(a, b);
		leaders.push_back(a);
		followers.push_back(b);
		++it;
	}
	leaders = fordJohnsonList(leaders);
	for (std::list<int>::iterator f = followers.begin(); f != followers.end(); ++f)
	{
		std::list<int>::iterator pos = leaders.begin();
		while (pos != leaders.end() && *pos < *f)
			++pos;
		leaders.insert(pos, *f);
	}
	return (leaders);
}

void PmergeMe::process()
{
	double	vecTime;
	double	listTime;

	std::cout << "Before: ";
	displayContainer(vec);
	std::clock_t startVec = std::clock();
	std::vector<int> sortedVec = fordJohnsonVector(vec);
	std::clock_t endVec = std::clock();
	std::clock_t startList = std::clock();
	std::list<int> sortedList = fordJohnsonList(lst);
	std::clock_t endList = std::clock();
	std::cout << "After: ";
	vecTime = 1e6 * (endVec - startVec) / CLOCKS_PER_SEC;
	listTime = 1e6 * (endList - startList) / CLOCKS_PER_SEC;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vecTime << " us\n";
	std::cout << "Time to process a range of " << lst.size() << " elements with std::list : " << listTime << " us\n";
}

void PmergeMe::generateRandom(int n)
{
	int	num;

	std::srand(static_cast<unsigned int>(std::time(0)));
	for (int i = 0; i < n; ++i)
	{
		num = std::rand() % 10000;
		vec.push_back(num);
		lst.push_back(num);
	}
}
