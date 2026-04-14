/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:59 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/19 16:47:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <cstdlib>
# include <iostream>
# include <string>

class Harl
{
  public:
	Harl();
	~Harl();
	void harlFilter(std::string level);

  private:
	void debug();
	void info();
	void warning();
	void error();
	std::string levels[4];
};

#endif