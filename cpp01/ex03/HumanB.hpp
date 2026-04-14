/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:56:15 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/15 12:12:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"
# include <iostream>
# include <string>

class HumanB
{
  private:
	std::string name;
	Weapon *weapon;

  public:
	HumanB(const std::string &name);
	~HumanB();
	void setWeapon(Weapon &weapon);
	void attack() const;
};

#endif