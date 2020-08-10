/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:44:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 17:44:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <iostream>
#include <list>
#include <vector>

#include "easyfind.hpp"

template<typename T>
	void
	do_test(T &container, int number)
	{
		if (easyfind(container, number))
			std::cout << "there is a " << number << " in the container" << std::endl;
		else
			std::cout << "there is no " << number << " in the container" << std::endl;
	}

int
main(void)
{
	std::cout << "--- A LIST ---" << std::endl;
	std::list<int> lst;

	for (int index = 0; index < 100; ++index)
		lst.push_back(index * 2);

	do_test(lst, 16);
	do_test(lst, 32);
	do_test(lst, 65);

	std::cout << std::endl << "--- A VECTOR ---" << std::endl;
	std::vector<int> vctor;

	for (int index = 0; index < 100; ++index)
		vctor.push_back(index * 2);

	do_test(vctor, 16);
	do_test(vctor, 32);
	do_test(vctor, 65);

	std::cout << std::endl << "--- A SET ---" << std::endl;
	int ints[] = { 1, 2, 65 };
	std::set<int> st(ints, ints + sizeof(ints) / sizeof(int));

	do_test(st, 16);
	do_test(st, 32);
	do_test(st, 65);
}
