/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 08:24:39 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/22 11:56:19 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include "iostream"
# include <cmath>

class Fixed
{
  private:
	int value;
	static const int rawBits = 8;

  public:
	//	# Constructor & Destructor #
	Fixed();
	Fixed(const int n);
	Fixed(const float f);
	Fixed(const Fixed &copy);
	Fixed &operator=(const Fixed &copy);
	~Fixed();

	//	# Comparisons operators #
	bool operator>(const Fixed &copy) const;
	bool operator<(const Fixed &copy) const;
	bool operator>=(const Fixed &copy) const;
	bool operator<=(const Fixed &copy) const;
	bool operator==(const Fixed &copy) const;
	bool operator!=(const Fixed &copoy) const;

	//	# Arithmetic operators #
	Fixed operator+(const Fixed &other) const;
	Fixed operator-(const Fixed &other) const;
	Fixed operator*(const Fixed &other) const;
	Fixed operator/(const Fixed &other) const;

	//	# Increments & Decrements operators #
	Fixed &operator++();
	Fixed operator++(int);
	Fixed &operator--();
	Fixed operator--(int);

	//	# Overload member functions #
	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);

	//	# Getter & Setter #
	int getRawBits() const;
	void setRawBits(int const raw);

	//	# Conversion member functions #
	float toFloat() const;
	int toInt() const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif