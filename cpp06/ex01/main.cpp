/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:45:36 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/24 19:56:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int	main(void)
{
	Data		data;
	uintptr_t	raw;
	Data		*ptr;

	data.name = "Baptiste";
	data.age = 36;
	std::cout << "Original Data: " << std::endl;
	std::cout << "Name: " << data.name << ", Age: " << data.age << std::endl;
	std::cout << "Adress: " << &data << std::endl;
	raw = Serializer::serialize(&data);
	std::cout << "\nSerialized value (uintptr_t): " << raw << std::endl;
	ptr = Serializer::deserialize(raw);
	std::cout << "\nDeserialized Data: " << std::endl;
	std::cout << "Name: " << ptr->name << ", Age: " << ptr->age << std::endl;
	std::cout << "Adress: " << ptr << std::endl;
	if (ptr == &data)
		std::cout << "\n✅ Success: Pointers are identical!" << std::endl;
	else
		std::cout << "\n❌ Error: Pointers are different!" << std::endl;
	return (0);
}
