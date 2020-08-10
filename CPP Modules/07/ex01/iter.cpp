/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 11:57:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template<class T>
	void
	iter(T *arr, size_t length, void (*consumer)(const T &))
	{
		if (!arr)
			return;

		for (size_t index = 0; index < length; ++index)
		{
			(*consumer)(arr[index]);
		}
	}

template<class T>
	void
	print(const T &x)
	{
		std::cout << x << std::endl;
	}

static void
print_int(const int &x)
{
	std::cout << x << std::endl;
}

static void
print_string(const std::string &x)
{
	std::cout << x << std::endl;
}

int
main(void)
{
	int ints[] = { 1, 3, 5, 7, 9 };
	std::string strings[] = { "Hello", "World", "From", "The", "iter", "template" };

	std::cout << "--- INTS form existing function ---" << std::endl;
	iter(ints, 5, print_int);

	std::cout << std::endl << "--- STRINGS form existing function ---" << std::endl;
	iter(strings, 6, print_string);

	std::cout << std::endl << "--- INTS form template function ---" << std::endl;
	iter(ints, 5, print);

	std::cout << std::endl << "--- STRINGS form template function ---" << std::endl;
	iter(strings, 6, print);
}
