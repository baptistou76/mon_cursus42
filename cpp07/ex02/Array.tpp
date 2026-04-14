/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:59:32 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 12:43:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T> Array<T>::Array() : _data(NULL), _size(0)
{
}

template <typename T> Array<T>::Array(unsigned int n) : _data(new T[n]),
	_size(n)
{
	for (unsigned int i = 0; i < n; i++)
		_data[i] = T();
}

template <typename T> Array<T>::Array(const Array &copy) : _data(NULL), _size(0)
{
	*this = copy;
}

template <typename T> Array<T> &Array<T>::operator=(const Array &copy)
{
	if (this != &copy)
	{
		delete[](_data);
		_size = copy._size;
		_data = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			_data[i] = copy._data[i];
	}
	return (*this);
}

template <typename T> Array<T>::~Array()
{
	delete[](_data);
}

template <typename T> T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
	{
		std::ostringstream oss;
		oss << "Index: " << index << " out of range (size: " << _size << ")";
		throw std::out_of_range(oss.str());
	}
	return (_data[index]);
}

template <typename T> const T &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
	{
		std::ostringstream oss;
		oss << "Index: " << index << " out of range (size: " << _size << ")";
		throw std::out_of_range(oss.str());
	}
	return (_data[index]);
}

template <typename T> unsigned int Array<T>::size() const
{
	return (_size);
}
