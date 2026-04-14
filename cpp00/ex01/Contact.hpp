/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:14:20 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/13 18:48:17 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <cctype>
# include <iomanip>
# include <iostream>
# include <limits>
# include <string>

class Contact
{
  private:
	std::string firstName;
	std::string lastName;
	std::string nickName;
	std::string phoneNumber;
	std::string darkestSecret;

  public:
	void setContact();
	void displaySummary(int index) const;
	void displayFull() const;
	bool isAllAlpha(const std::string &str);
	bool isAllDigits(const std::string &str);
};

#endif