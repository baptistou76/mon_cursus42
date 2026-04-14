/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:15:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 13:30:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <iostream>
# include <list>
# include <stdexcept>
# include <vector>

template <typename T> typename T::iterator easyfind(T &container, int value);
template <typename T> typename T::const_iterator easyfind(const T &container,
	int value);

# include "easyfind.tpp"

#endif