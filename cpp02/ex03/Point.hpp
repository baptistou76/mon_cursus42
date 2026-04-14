/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:08:10 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/22 13:20:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
  private:
	const Fixed x;
	const Fixed y;

  public:
	Point();
	Point(const float x, const float y);
	Point(const Point &copy);
	Point &operator=(const Point &copy);
	~Point();

	const Fixed &getX() const;
	const Fixed &getY() const;
};

std::ostream &operator<<(std::ostream &out, Point const Point);

#endif