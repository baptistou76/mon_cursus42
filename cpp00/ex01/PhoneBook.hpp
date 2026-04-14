/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:24:34 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/13 19:27:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
  private:
	Contact contact[8];
	int total;

  public:
	PhoneBook() : total(0)
	{
	}
	void addContact();
	void searchContact() const;
	void displayHeader() const;
	void displayAllSummary() const;
	void displayIndexDetails(int count) const;
};

#endif