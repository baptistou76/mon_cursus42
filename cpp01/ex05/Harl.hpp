/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:09:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/18 19:37:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

class Harl
{
  public:
	Harl();
	~Harl();
	void complain(std::string level);

  private:
	void debug();
	void info();
	void warning();
	void error();
	void (Harl::*complaints[4])(void);
	std::string levels[4];
};

#endif