/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:04:31 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/22 12:02:15 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// # ---------- Constructors & Destructor ---------- #

Fixed::Fixed() : value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	value = n << rawBits;
}

Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	value = roundf(f * (1 << rawBits));
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// # ---------- Assignation ---------- #

Fixed &Fixed::operator=(const Fixed &copy)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		value = copy.value;
	return (*this);
}

// # ---------- Comparisons ---------- #

bool Fixed::operator>(const Fixed &copy) const
{
	return (value > copy.value);
}

bool Fixed::operator<(const Fixed &copy) const
{
	return (value < copy.value);
}

bool Fixed::operator>=(const Fixed &copy) const
{
	return (value >= copy.value);
}

bool Fixed::operator<=(const Fixed &copy) const
{
	return (value <= copy.value);
}

bool Fixed::operator==(const Fixed &copy) const
{
	return (value == copy.value);
}

bool Fixed::operator!=(const Fixed &copy) const
{
	return (value != copy.value);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return ((a < b) ? a : b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return ((a < b) ? a : b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return ((a > b) ? a : b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return ((a > b) ? a : b);
}

// # ---------- Arithmetic ---------- #

Fixed Fixed::operator+(const Fixed &copy) const
{
	return (Fixed(this->toFloat() + copy.toFloat()));
}

Fixed Fixed::operator-(const Fixed &copy) const
{
	return (Fixed(this->toFloat() - copy.toFloat()));
}

Fixed Fixed::operator*(const Fixed &copy) const
{
	return (Fixed(this->toFloat() * copy.toFloat()));
}

Fixed Fixed::operator/(const Fixed &copy) const
{
	return (Fixed(this->toFloat() / copy.toFloat()));
}

// # ---------- Conversion ---------- #

float Fixed::toFloat() const
{
	return ((float)value / (1 << rawBits));
}
int Fixed::toInt() const
{
	return (value >> rawBits);
}

// # ---------- Getter & Setter ---------- #

int Fixed::getRawBits() const
{
	return (value);
}

void Fixed::setRawBits(int const raw)
{
	value = raw;
}

// # ---------- Increment & Decrement ---------- #

Fixed &Fixed::operator++()
{
	this->value++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	this->value++;
	return (tmp);
}

Fixed &Fixed::operator--()
{
	this->value--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	this->value--;
	return (tmp);
}

// # ---------- Operator overload ---------- #

std::ostream &operator<<(std::ostream &out, const Fixed &Fixed)
{
	out << Fixed.toFloat();
	return (out);
}
