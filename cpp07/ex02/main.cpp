#include "Array.hpp"

#define MAX_VAL 750

int	main(int, char **)
{
	Array<int> numbers(MAX_VAL);
	int *mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	// SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return (1);
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	delete[] mirror;
	std::cout << "\n=== Test de deep copy ===" << std::endl;
	Array<int> original(5);
	for (unsigned int i = 0; i < original.size(); i++)
		original[i] = i + 1;

	Array<int> copy = original;
	copy[0] = 999;

	std::cout << "Original[0] = " << original[0] << std::endl;
	std::cout << "Copy[0]     = " << copy[0] << std::endl;

	if (original[0] == copy[0])
		std::cout << "❌ Deep copy failed (shallow copy)" << std::endl;
	else
		std::cout << "✅ Deep copy successful" << std::endl;

	std::cout << "\n=== Test avec des strings ===" << std::endl;
	Array<std::string> words(3);
	words[0] = "Hello";
	words[1] = "42";
	words[2] = "World";

	for (unsigned int i = 0; i < words.size(); i++)
		std::cout << "words[" << i << "] = " << words[i] << std::endl;
	return (0);
}