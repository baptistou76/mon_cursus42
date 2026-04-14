/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:39:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/14 11:18:22 by bcaumont         ###   ########.fr       */
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

  public:
	Zombie(std::string name);
	~Zombie();

	void announce(void);
};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

#endif