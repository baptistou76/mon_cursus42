/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:33:42 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 12:47:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <cstdlib>
# include <ctime>
# include <iostream>
# include <limits>
# include <sstream>
# include <stdexcept>

template <typename T> class Array
{
  private:
	T *_data;
	unsigned int _size;

  public:
	Array();
	Array(unsigned int n);
	Array(const Array &copy);
	Array &operator=(const Array &copy);
	~Array();

	T &operator[](unsigned int index);
	const T &operator[](unsigned int index) const;
	unsigned int size() const;
};

# include "Array.tpp"

#endif