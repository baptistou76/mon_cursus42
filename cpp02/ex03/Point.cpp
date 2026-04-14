/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:18:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/23 23:30:48 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0)
{
}

Point::Point(const float x, const float y) : x(x), y(y)
{
}

Point::Point(const Point &copy) : x(copy.x), y(copy.y)
{
}
Point &Point::operator=(const Point &copy)
{
	(void)copy;
	return (*this);
}

Point::~Point()
{
}

const Fixed &Point::getX() const
{
	return (this->x);
}

const Fixed &Point::getY() const
{
	return (this->y);
}

std::ostream &operator<<(std::ostream &out, Point const Point)
{
	out << "x: " << Point.getX() << " / y: " << Point.getY() << std::endl;
	return (out);
}
