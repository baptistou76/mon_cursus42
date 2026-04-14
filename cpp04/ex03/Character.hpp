/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:50:34 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/30 01:03:17 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"

class Character : public ICharacter
{
  private:
	std::string name;
	AMateria *inventory[4];

  public:
	Character(std::string const &name);
	Character(Character const &copy);
	Character &operator=(Character const &copy);
	virtual ~Character();

	virtual std::string const &getName() const;
	virtual void equip(AMateria *m);
	virtual void unequip(int index);
	virtual void use(int index, ICharacter &target);
};

#endif