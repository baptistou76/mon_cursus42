#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include "AMateria.hpp"
# include <string>
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define BLUE "\033[34m"

class	AMateria;

class ICharacter
{
  private:
	std::string name;

  public:
	virtual ~ICharacter()
	{
	}
	virtual std::string const &getName() const = 0;
	virtual void equip(AMateria *m) = 0;
	virtual void unequip(int index) = 0;
	virtual void use(int index, ICharacter &target) = 0;
};

#endif
