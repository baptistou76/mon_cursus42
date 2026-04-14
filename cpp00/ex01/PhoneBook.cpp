/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:30:39 by bcaumont          #+#    #+#             */
/*   Updated: 2025/08/13 19:27:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void PhoneBook::addContact()
{
	Contact	newContact;

	newContact.setContact();
	if (!std::cin)
		return ;
	contact[total % 8] = newContact;
	total++;
}

void PhoneBook::searchContact() const
{
	int count;
	if (total < 8)
		count = total;
	else
		count = 8;
	if (count == 0)
	{
		std::cout << "PhoneBook is empty.\n" << std::endl;
		return ;
	}
	displayHeader();
	displayAllSummary();
	displayIndexDetails(count);
}

void PhoneBook::displayHeader() const
{
	std::cout << "---------------------------------------------\n";
	std::cout << "|" << std::setw(10) << "Index"
				<< "|" << std::setw(10) << "FirstName"
				<< "|" << std::setw(10) << "LastName"
				<< "|" << std::setw(10) << "Nickname"
				<< "|\n";
	std::cout << "---------------------------------------------\n";
}

void PhoneBook::displayAllSummary() const
{
	if (total > 0)
		contact[0].displaySummary(1);
	if (total > 1)
		contact[1].displaySummary(2);
	if (total > 2)
		contact[2].displaySummary(3);
	if (total > 3)
		contact[3].displaySummary(4);
	if (total > 4)
		contact[4].displaySummary(5);
	if (total > 5)
		contact[5].displaySummary(6);
	if (total > 6)
		contact[6].displaySummary(7);
	if (total > 7)
		contact[7].displaySummary(8);
	std::cout << "---------------------------------------------\n";
}

void PhoneBook::displayIndexDetails(int count) const
{
	std::string input;
	int index;

	std::cout << "Enter index (1-8): ";
	std::getline(std::cin, input);
	if (input.length() != 1 || input[0] < '1' || input[0] > '8')
	{
		std::cout << "Invalid input.\n";
		return ;
	}
	index = input[0] - '1';
	if (index >= count)
	{
		std::cout << "No contact at this index.\n";
		return ;
	}
	contact[index].displayFull();
}

int	main(void)
{
	PhoneBook	book;

	std::string input;
	while (std::cin)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, input);
		if (std::cin.eof() || !std::cin)
			break ;
		if (input == "ADD" || input == "add")
			book.addContact();
		else if (input == "SEARCH" || input == "search")
			book.searchContact();
		else if (input == "EXIT" || input == "exit")
			break ;
		else
			std::cout << "Invalid command.\n" << std::endl;
	}
	return (0);
}
