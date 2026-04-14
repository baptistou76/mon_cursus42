/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 06:10:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/29 06:30:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include "Animal.hpp"
# include "WrongAnimal.hpp"

class Brain
{
  private:
	std::string ideas[100];

  public:
	Brain();
	Brain(const Brain &copy);
	Brain &operator=(const Brain &copy);
	virtual ~Brain();

	void setIdeas(int index, const std::string &idea);
	std::string getIdea(int index) const;
};

#endif