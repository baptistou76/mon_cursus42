/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:49:42 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/30 20:50:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <algorithm>
# include <cctype>
# include <fstream>
# include <iomanip>
# include <iostream>
# include <list>
# include <map>
# include <sstream>
# include <stdexcept>
# include <string>
# include <vector>

class BitcoinExchange
{
  private:
	std::map<std::string, double> _db;
	bool isValidate(const std::string &data) const;
	std::string trim(const std::string &str) const;
	std::string formatDouble(double v) const;

  public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange &operator=(const BitcoinExchange &copy);
	~BitcoinExchange();

	bool loadDatabase(const std::string &filename);
	void processInput(const std::string &filename) const;
};

#endif
