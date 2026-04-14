/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:35:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/02 16:12:46 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		_db = copy._db;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trim(const std::string &str) const
{
	size_t b = 0;
	while (b < str.size() && std::isspace(static_cast<unsigned char>(str[b])))
		b++;
	size_t e = str.size();
	while (e > b && std::isspace(static_cast<unsigned char>(str[e - 1])))
		e--;
	return (str.substr(b, e - b));
}

bool BitcoinExchange::isValidate(const std::string &date) const
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}
	int year = 0;
	int month = 0;
	int day = 0;
	std::istringstream _year(date.substr(0, 4));
	std::istringstream _month(date.substr(5, 2));
	std::istringstream _day(date.substr(8, 2));
	if (!(_year >> year) || !(_month >> month) || !(_day >> day))
		return (false);
	if (month < 1 || month > 12)
		return (false);
	static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
		30, 31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		maxDay = 29;
	if (day < 1 || day > maxDay)
		return (false);
	return (true);
}

std::string BitcoinExchange::formatDouble(double v) const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(10) << v;
	std::string s = oss.str();
	while (!s.empty() && s[s.size() - 1] == '0')
		s.erase(s.size() - 1);
	if (!s.empty() && s[s.size() - 1] == '.')
		s.erase(s.size() - 1);
	if (s.empty())
		s = '0';
	return (s);
}

bool BitcoinExchange::loadDatabase(const std::string &filename)
{
	size_t	comma;
	double	rate;

	std::ifstream f(filename.c_str());
	if (!f.is_open())
		return (false);
	std::string line;
	while (std::getline(f, line))
	{
		if (line.empty())
			continue ;
		if (line.find("date") != std::string::npos
			&& line.find("exchange_rate") != std::string::npos)
			continue ;
		comma = line.find(',');
		if (comma == std::string::npos)
			continue ;
		std::string date = trim(line.substr(0, comma));
		std::string rateStr = trim(line.substr(comma + 1));
		if (!isValidate(date))
			continue ;
		std::istringstream(rateStr) >> rate;
		_db[date] = rate;
	}
	return (true);
}

void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream in(filename.c_str());
	if (!in.is_open())
	{
		std::cerr << "Error: couldn't open file." << std::endl;
		return ;
	}
	std::string line;
	bool firstLine = true;
	while (std::getline(in, line))
	{
		if (line.empty())
			continue ;
		if (firstLine)
		{
			if (line.find("date") != std::string::npos
				&& line.find("value") != std::string::npos)
			{
				firstLine = false;
				continue ;
			}
			firstLine = false;
		}
		size_t pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cout << "Error: bad input => " << trim(line) << std::endl;
			continue ;
		}
		std::string date = trim(line.substr(0, pipe));
		std::string valueStr = trim(line.substr(pipe + 1));
		if (!isValidate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue ;
		}
		double value;
		std::istringstream iss(valueStr);
		if (!(iss >> value))
		{
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue ;
		}
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue ;
		}
		std::map<std::string,
			double>::const_iterator it = _db.lower_bound(date);
		if (it == _db.end() || it->first != date)
		{
			if (it == _db.begin())
			{
				std::cout << "Error: no exchange rate available for " << date << std::endl;
				continue ;
			}
			it--;
		}
		double rate = it->second;
		double result = value * rate;
		std::cout << date << " => " << formatDouble(value) << " = " << formatDouble(result) << std::endl;
	}
}
