/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:06:55 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/15 07:54:46 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <cctype>
# include <iostream>
# include <string>

class Zombie
{
  private:
	std::string name;
	int index;

  public:
	Zombie();
	~Zombie();
	void announce(void);
	void setName(std::string name);
};

Zombie	*zombieHorde(int N, std::string name);
Zombie	*newZombie(std::string name);

#endif