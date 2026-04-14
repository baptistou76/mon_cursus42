/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:23:47 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/30 18:13:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <algorithm>
# include <deque>
# include <iostream>
# include <list>
# include <stack>
# include <stdexcept>
# include <vector>

template <typename T, typename Container = std::deque<T> > class MutantStack : public std::stack<T,
	Container>
{
  public:
	//   Iterator types
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;
	typedef typename Container::reverse_iterator reverse_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;
	// Constructors
	MutantStack();
	MutantStack(const MutantStack<T, Container> &copy);
	MutantStack<T, Container> &operator=(const MutantStack<T, Container> &copy);
	~MutantStack();
	// Iterators methods
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
};

# include "MutantStack.tpp"

#endif