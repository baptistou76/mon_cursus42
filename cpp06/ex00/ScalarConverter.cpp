/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:44:18 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/24 18:24:54 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
	(void)copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy)
{
	(void)copy;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

bool ScalarConverter::isChar(const std::string &param)
{
	return (param.length() == 1 && !std::isdigit(param[0]));
}

bool ScalarConverter::isInt(const std::string &param)
{
	char	*end;

	std::strtol(param.c_str(), &end, 10);
	return (*end == '\0');
}

bool ScalarConverter::isFloat(const std::string &param)
{
	char	*end;

	if (param == "-inff" || param == "+inff" || param == "nanf")
		return (true);
	if (param[param.length() - 1] != 'f')
		return (false);
	std::string core = param.substr(0, param.length() - 1);
	std::strtod(core.c_str(), &end);
	return (*end == '\0' && core.find('.') != std::string::npos);
}

bool ScalarConverter::isDouble(const std::string &param)
{
	char	*end;

	if (param == "-inf" || param == "+inf" || param == "nan")
		return (true);
	if (param.find('.') == std::string::npos)
		return (false);
	std::strtod(param.c_str(), &end);
	return (*end == '\0');
}

void ScalarConverter::printChar(double value)
{
	std::cout << "char: ";
	if (std::isnan(value) || value < 0 || value > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(value)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
}

void ScalarConverter::printInt(double value)
{
	std::cout << "int: ";
	if (std::isnan(value) || value > std::numeric_limits<int>::max()
		|| value < std::numeric_limits<int>::min())
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::printFloat(double value)
{
	std::cout << "float: ";
	std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
}

void ScalarConverter::printDouble(double value)
{
	std::cout << "double: ";
	std::cout << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;
}

void ScalarConverter::convert(const std::string &param)
{
	double	value;

	value = 0.0;
	if (isChar(param))
		value = static_cast<double>(param[0]);
	else if (isInt(param))
		value = static_cast<double>(std::atoi(param.c_str()));
	else if (isFloat(param))
		value = static_cast<double>(std::atof(param.c_str()));
	else if (isDouble(param))
		value = std::atof(param.c_str());
	else
	{
		std::cout << "Error: invalid param" << std::endl;
		return ;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
