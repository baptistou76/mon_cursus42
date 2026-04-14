/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:29:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/13 20:19:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

bool Contact::isAllDigits(const std::string &str)
{
	size_t	i;

	i = 0;
	if (str.empty())
		return (false);
	while (i < str.length())
	{
		if ((!isdigit(str[i])))
			return (false);
		i++;
	}
	return (true);
}

bool Contact::isAllAlpha(const std::string &str)
{
	size_t	i;

	i = 0;
	if (str.empty())
		return (false);
	while (i < str.length())
	{
		if ((!isalpha(str[i])))
			return (false);
		i++;
	}
	return (true);
}

static std::string truncate(std::string str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

void Contact::setContact()
{
	do
	{
		std::cout << "First name: ";
		if (!std::getline(std::cin, firstName))
		{
			std::cout << "End of programm.\n";
			return ;
		}
		if (!isAllAlpha(firstName))
			std::cout << "Invalid character! Only letters are available.\n";
	} while (!isAllAlpha(firstName));
	if (!std::cin)
		return ;
	do
	{
		std::cout << "Last name: ";
		if (!std::getline(std::cin, lastName))
		{
			std::cout << "End of programm.\n";
			return ;
		}
		if (!isAllAlpha(lastName))
			std::cout << "Invalid character! Only letters are available.\n";
	} while (!isAllAlpha(lastName));
	do
	{
		std::cout << "Nickname: ";
		if (!std::getline(std::cin, nickName))
		{
			std::cout << "End of programm.\n";
			return ;
		}
		if (!isAllAlpha(nickName))
			std::cout << "Invalid character! Only letters are available.\n";
	} while (!isAllAlpha(nickName));
	do
	{
		std::cout << "Phone number: ";
		if (!std::getline(std::cin, phoneNumber))
		{
			std::cout << "End of programm.\n";
			return ;
		}
		if (!isAllDigits(phoneNumber))
			std::cout << "Invalid character! Only digits are available.\n";
	} while (!isAllDigits(phoneNumber));
	do
	{
		std::cout << "Darkest secret: ";
		if (!std::getline(std::cin, darkestSecret))
		{
			std::cout << "End of programm.\n";
			return ;
		}
		if (!isAllAlpha(darkestSecret))
			std::cout << "Invalid character! Only letters are available.\n";
	} while (!isAllAlpha(darkestSecret));
}

void Contact::displaySummary(int index) const
{
	std::cout << "|" << std::setw(10) << index;
	std::cout << "|" << std::setw(10) << truncate(firstName);
	std::cout << "|" << std::setw(10) << truncate(lastName);
	std::cout << "|" << std::setw(10) << truncate(nickName);
	std::cout << "|\n";
}

void Contact::displayFull() const
{
	std::cout << "First name: " << firstName << "\n";
	std::cout << "Last name: " << lastName << "\n";
	std::cout << "Nickname: " << nickName << "\n";
	std::cout << "Phone number: " << phoneNumber << "\n";
	std::cout << "Darkest secret: " << darkestSecret << "\n";
}
